#define _GNU_SOURCE

#include "crab_action.h"
#include "term_colour.h"
#include "history.h"
#include "alias.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *crab_action_error_get_text(int error_code) {
    switch (error_code) {
        case CRAB_ACTION_ERROR_SUCCESS:
            return "Success.";
        case CRAB_ACTION_GENERIC_ERROR:
            return "Generic error.";
        case CRAB_ACTION_ERROR_FORK_FAILED:
            return "Fork failed.";
        case CRAB_ACTION_ERROR_EXEC_FAILED:
            return "Exec failed.";
        case HISTORY_DISPLAY_ERROR:
            return "History failed to display.";
        default:
            return "Unknown error.";
    }
}

int crab_action_find_action(char *command) {
    if (command == NULL) {
        return CRAB_ACTION_NO_ACTION;
    }
    if (!strcmp(command, "exit")) {
        return CRAB_ACTION_EXIT;
    }
    if (!strcmp(command, "cd")) {
        return CRAB_ACTION_CD;
    }
    if (!strcmp(command, "pwd")) {
        return CRAB_ACTION_PWD;
    }
    if (!strcmp(command, "colour")) {
        return CRAB_ACTION_COLOUR;
    }
    if (!strncmp(command, "history", 7)) {
        return CRAB_ACTION_HIST;
    }
    if (!strcmp(command, "ad")) {
        return CRAB_ACTION_AD;
    }
    return CRAB_ACTION_EXECUTE;
}

int crab_action_perform_action(int action, char **argv) {
    char *temp;
    int numCmds;
    int pos;

    switch (action) {
        case CRAB_ACTION_NO_ACTION:
            return CRAB_ACTION_ERROR_SUCCESS;
            break;

        case CRAB_ACTION_EXECUTE:
            return crab_action_fork_exec_wait(argv[0], argv);
            break;

            /* Exit crab */
        case CRAB_ACTION_EXIT:
            freeHistory();
            exit(0);
            return CRAB_ACTION_GENERIC_ERROR;
            break;

            /* Change directory */
        case CRAB_ACTION_CD:
            if (argv[1] != NULL) {
                if ((pos = is_alias(argv[1])) >= 0) {
                    if (chdir(get_dir(pos))) {
		      printf("Unable to find directory.\n");
                        return CRAB_ACTION_ERROR_SUCCESS;
                    }
                    return CRAB_ACTION_ERROR_SUCCESS;
                }
                if (chdir(argv[1])) {
		  printf("Unable to find directory.\n");
                    return CRAB_ACTION_ERROR_SUCCESS;
                }
                return CRAB_ACTION_ERROR_SUCCESS;
            } else {
                if (temp = getenv("HOME")) {
                    return chdir(temp);
                }
		printf("Unable to find directory.\n");
                return CRAB_ACTION_ERROR_SUCCESS;
            }
            break;

            /* Print working directory */
        case CRAB_ACTION_PWD:
            temp = get_current_dir_name();
            write(1, temp, strlen(temp));
            write(1, "\n", 1);
            free(temp);
            return CRAB_ACTION_ERROR_SUCCESS;
            break;

            /* Change terminal colour */
        case CRAB_ACTION_COLOUR:
            if (argv[1] == NULL) {
                return CRAB_ACTION_GENERIC_ERROR;
            }
            if (term_colour_set_colour(argv[1]) == TERM_COLOUR_ERROR_SUCCESS) {
                return CRAB_ACTION_ERROR_SUCCESS;
            } else {
                return CRAB_ACTION_GENERIC_ERROR;
            }

            /* Display command history */
        case CRAB_ACTION_HIST:
            if (argv[1] == NULL) {
                numCmds = 10;
            } else {
                numCmds = atoi(argv[1]);
                if (numCmds == 0) {
                    return HISTORY_DISPLAY_ERROR;
                }
            }
            if (displayHist(numCmds) == DISPLAY_HISTORY_ERROR_SUCCESS) {
                return CRAB_ACTION_ERROR_SUCCESS;
            } else {
                return HISTORY_DISPLAY_ERROR;
            }
        /* Alias Directory - usage: ad help */
        case CRAB_ACTION_AD:
            if (argv[1] == NULL) {
                temp = get_current_dir_name();
                if (add_alias("prev", temp) == 0)
                    return CRAB_ACTION_ERROR_SUCCESS;
                else
                    return CRAB_ACTION_GENERIC_ERROR;
            }

            if (argv[1] != NULL && argv[2] == NULL) {
                /* help */
                if (strcmp(argv[1], "help") == 0) {
                    if (print_alias_help() == 0)
                        return CRAB_ACTION_ERROR_SUCCESS;
                    else
                        return CRAB_ACTION_GENERIC_ERROR;
                }
                /* print */
                if (strcmp(argv[1], "print") == 0) {
                    if (print_alias() == 0)
                        return CRAB_ACTION_ERROR_SUCCESS;
                    else
                        return CRAB_ACTION_GENERIC_ERROR;
                }
                /* save */
                if (strcmp(argv[1], "save") == 0) {
                    if (save_alias() == 0)
                        return CRAB_ACTION_ERROR_SUCCESS;
                    else
                        return CRAB_ACTION_GENERIC_ERROR;
                }
                /* reset */
                if (strcmp(argv[1], "reset") == 0) {
                    if (reset_alias() == 0)
                        return CRAB_ACTION_ERROR_SUCCESS;
                    else
                        return CRAB_ACTION_GENERIC_ERROR;
                }
                /* set alias with name = to curr dir */
                temp = get_current_dir_name();
                if (add_alias(argv[1], temp) == 0)
                    return CRAB_ACTION_ERROR_SUCCESS;
                else
                    return CRAB_ACTION_GENERIC_ERROR;
            }

            if (argv[1] != NULL && argv[2] != NULL) {
                /* remove */
                if (strcmp(argv[1], "remove") == 0) {
                    remove_alias(argv[2]);
                    return CRAB_ACTION_ERROR_SUCCESS;
                }
                /* findn */
                if (strcmp(argv[1], "findn") == 0) {
                    find_alias_name(argv[2]);
                    return CRAB_ACTION_ERROR_SUCCESS;
                }
                /* findd */
                if (strcmp(argv[1], "findd") == 0) {
                    find_alias_dir(argv[2]);
                    return CRAB_ACTION_ERROR_SUCCESS;
                }
                if (add_alias(argv[1], argv[2]) == 0)
                    return CRAB_ACTION_ERROR_SUCCESS;
                else
                    return CRAB_ACTION_GENERIC_ERROR;
            }

        default:
            return CRAB_ACTION_GENERIC_ERROR;
    }
}

int crab_action_fork_exec_wait(char *command, char **argv) {
    pid_t child_pid;

    /* Fork and check if fork failed */
    child_pid = fork();
    if (child_pid < 0) {
        return CRAB_ACTION_ERROR_FORK_FAILED;
    }

    /* Child execs, parent waits for child to die */
    if (child_pid) {
        wait(NULL);
    } else {
        execvp(command, argv);
        return CRAB_ACTION_ERROR_EXEC_FAILED;
    }

    return CRAB_ACTION_ERROR_SUCCESS;
}
