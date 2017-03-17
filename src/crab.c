#include "crab.h"

int crab_split_command_string(char *command_string, char ***argv){
	size_t curr_pos;
	size_t start_pos;
	size_t argv_size;
	size_t argv_allocated_size;
	char temp;

	/* Allocate initial array for argv */
	argv_size = 0;
	argv_allocated_size = 1;
	(*argv) = malloc(argv_allocated_size * sizeof(char*));

	/* Begin splitting */
	curr_pos = 0;
	while(command_string[curr_pos] != '\0' &&
				command_string[curr_pos] != '\n'){
		/* Advance past any whitespace */
		while(command_string[curr_pos] == ' '){
			curr_pos++;
		}
		/* Check if arg is quoted */
		if(command_string[curr_pos] == '"'){
			curr_pos++;
			start_pos = curr_pos;
			while(command_string[curr_pos] != '"' &&
						command_string[curr_pos] != '\0' &&
								command_string[curr_pos] != '\n'){
				curr_pos++;
			}
			if(command_string[curr_pos] == '\0'){
				return CRAB_ERROR_UNMATCHED_QUOTE;
			}
			command_string[curr_pos] = '\0';
			if(argv_size + 1 >= argv_allocated_size){
				argv_allocated_size *= 2;
				(*argv) = realloc((*argv),
						argv_allocated_size *
						sizeof(char*));
			}
			(*argv)[argv_size] = strdup(command_string + start_pos);
			argv_size++;
			command_string[curr_pos] = '"';
		}
		else{
			start_pos = curr_pos;
			while(command_string[curr_pos] != ' ' &&
				       command_string[curr_pos] != '\0' &&
						 		command_string[curr_pos] != '\n'){
				curr_pos++;
			}
			temp = command_string[curr_pos];
			command_string[curr_pos] = '\0';
			if(argv_size + 1 >= argv_allocated_size){
				argv_allocated_size *= 2;
				(*argv) = realloc((*argv),
						argv_allocated_size *
						sizeof(char**));
			}
			(*argv)[argv_size] = strdup(command_string + start_pos);
			argv_size++;
			command_string[curr_pos] = temp;
		}
		if(command_string[curr_pos] != '\0' &&
				command_string[curr_pos] != '\n'){
			curr_pos++;
		}
	}
	(*argv)[argv_size] = NULL;

	return 0;
}

/* Checks a command string for any | characters
 *
 * command_string - the complete command string
 */
int crab_isPiped(char *command_string)
{
	if(strchr(command_string, '|') == 0)
	{
		return 0;
	}
	return 1;
}

/* Splits a command string based on pipe characters
 * Executes any number of piped commands
 * 
 * command_string - the complete command string
 */
int crab_split_exec_piped_command(char* command_string) {
 	char *aCmd[MAXCMDS][MAXARGS];
 	int cmdCounter, i, nargs, forkErr;
 	char *nextCmd;

 	cmdCounter = 0;
 	while((nextCmd=(char *)strrchr(command_string, '|')) != NULL) {
    	*nextCmd = '\0';
		nextCmd++;
		aCmd[cmdCounter][0] = nextCmd;
		cmdCounter++;
	}
	aCmd[cmdCounter][0] = command_string;
    cmdCounter++;

    /* Seperate each command into its args*/
    for(i = 0; i < cmdCounter; i++) {
    	aCmd[i][0] = (char *)strtok(aCmd[i][0], " \n");

      	/* Make sure a command follows a pipe */
    	if(aCmd[i][0] == NULL) {
    		printf("Error: Invalid command - command missing\n");
    		break;
    	}

    	nargs = 1;
    	aCmd[i][nargs] = (char *)strtok(NULL, " \n");

    	while(aCmd[i][nargs] != NULL) {
    		nargs++;
    		aCmd[i][nargs] = (char *)strtok(NULL, " \n");
    	}

    	/* Make sure we dont exceed max arg amount */
    	if(nargs > MAXARGS) {
      		printf("Error: Arg limit (20) exceeded\n");
      		continue;
    	}
    }

	/* Process commands */
	struct command commands[cmdCounter];
	int index = 0;
	for(i = cmdCounter - 1; i >= 0; i--)
	{
		commands[index].cmdstr = (const char**)aCmd[i];
		index++;
	}

	forkErr = fork_pipes(cmdCounter, commands);
  	if(forkErr < 0)
  	{
    	printf("Error: Invalid Command!\n");
    	exit(1);
  	}
    return 0;
}

/*
Spawn procedures for each command
params: in fd, out fd, command structure
returns: process ID
*/
int spawn_proc (int in, int out, struct command *cmd)
{
  pid_t pid;

  pid = fork();
  if(pid < 0) {
    perror("fork error!\n");
    exit(1);
  }
  if(pid == 0) {
    if(in != 0) {
      dup2(in, 0);
      close(in);
    }

    if(out != 1) {
      dup2(out, 1);
      close(out);
    }

    return execvp(cmd->cmdstr [0], (char * const *)cmd->cmdstr);
    printf("Error: Exec failed!\n");
    exit(1);
  }
  else {
    wait(NULL);
  }
  return pid;
}

/*
fork-execs any number of piped commands (or just one command)
params: number of commands, command structure
returns ret result from execvp - (errors handled by caller)
*/
int fork_pipes (int n, struct command *cmd) {
  int i;
  pid_t pid;
  int in, fd[2];

  pid = fork();
  if(pid < 0) {
    perror("fork error!\n");
    exit(1);
  }
  if(pid) {
    wait(NULL);
  } else {
    in = 0;
    for(i = 0; i < n - 1; ++i) {
      pipe(fd);
      pid = spawn_proc(in, fd[1], cmd + i);
      if(pid < 0) {
        exit(1);
      }
      close(fd[1]);
      in = fd[0];
    }

    if(in != 0) {
      dup2(in, 0);
    }

    return execvp (cmd[i].cmdstr [0], (char * const *)cmd[i].cmdstr);
    printf("Error: Exec failed!\n");
    exit(1);
  }

  return 0;
}