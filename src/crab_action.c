#define _GNU_SOURCE

#include "crab_action.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *crab_action_error_get_text(int error_code){
	switch(error_code){
		case CRAB_ACTION_GENERIC_ERROR:
		return "Generic error.";
		case CRAB_ACTION_ERROR_FORK_FAILED:
		return "Fork failed.";
		case CRAB_ACTION_ERROR_EXEC_FAILED:
		return "Exec failed.";
		default:
		return "Unknown error.";
	}
}

int crab_action_find_action(char *command){
	if(command == NULL){
		return CRAB_ACTION_NO_ACTION;
	}
	if(!strcmp(command, "exit")){
		return CRAB_ACTION_EXIT;
	}
	if(!strcmp(command, "cd")){
		return CRAB_ACTION_CD;
	}
	if(!strcmp(command, "pwd")){
		return CRAB_ACTION_PWD;
	}
	return CRAB_ACTION_EXECUTE;
}

int crab_action_perform_action(int action, char **argv){
	char *temp;

	switch(action){
		case CRAB_ACTION_NO_ACTION:
		return 0;
		break;

		case CRAB_ACTION_EXECUTE:
		return crab_action_fork_exec_wait(argv[0], argv);
		break;

		/* Exit crab */
		case CRAB_ACTION_EXIT:
		exit(0);
		return CRAB_ACTION_GENERIC_ERROR;
		break;

		/* Change directory */
		case CRAB_ACTION_CD:
		if(argv[1] != NULL){
			return chdir(argv[1]);
		}
		else{
			if(temp = getenv("HOME")){
				return chdir(temp);
			}
			return CRAB_ACTION_GENERIC_ERROR;
		}
		break;

		case CRAB_ACTION_PWD:
		temp = get_current_dir_name();
		write(1, temp, strlen(temp));
		write(1, "\n", 1);
		free(temp);
		break;

		default:
		return CRAB_ACTION_GENERIC_ERROR;
	}
}

int crab_action_fork_exec_wait(char *command, char **argv){
	pid_t child_pid;

	/* Fork and check if fork failed */
	child_pid = fork();
	if(child_pid < 0){
		return CRAB_ACTION_ERROR_FORK_FAILED;
	}

	/* Child execs, parent waits for child to die */
	if(child_pid){
		wait(NULL);
	}
	else{
		execvp(command, argv);
		return CRAB_ACTION_ERROR_EXEC_FAILED;
	}

	return 0;
}
