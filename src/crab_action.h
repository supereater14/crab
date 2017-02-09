#ifndef CRAB_ACTION_H
#define CRAB_ACTION_H

/* Error codes */
#define CRAB_ACTION_GENERIC_ERROR -1
#define CRAB_ACTION_ERROR_FORK_FAILED -2
#define CRAB_ACTION_ERROR_EXEC_FAILED -3

/* Actions */
#define CRAB_ACTION_EXECUTE 1
#define CRAB_ACTION_EXIT 2
#define CRAB_ACTION_CD 3
#define CRAB_ACTION_PWD 4

/* Generates error text for a provided error code
 *
 * error_code - The error code, provided by another crab_action function
 * returns - string containing error message
 */
char *crab_action_error_get_text(int error_code);

/* Reads a command string and determines an action code
 *
 * command - command string to interpret
 * returns - 0 on failure, action code otherwise
 */
int crab_action_find_action(char *command);

/*  Performs an action based on an action code
 *
 * action - action code
 * argv - argv for action
 * returns - 0 on success, nonzero otherwise
 */
int crab_action_perform_action(int action, char **argv);

/* Forks to background, execs a program and waits
 *
 * command - program to exec
 * argv - arguments for command
 * returns - 0 on success, nonzero on error
 */
int crab_action_fork_exec_wait(char *command, char **argv);

#endif
