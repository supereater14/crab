#ifndef CRAB_ACTION_H
#define CRAB_ACTION_H

/* Error codes */
#define CRAB_ACTION_ERROR_SUCCESS 0
#define CRAB_ACTION_GENERIC_ERROR -1
#define CRAB_ACTION_ERROR_FORK_FAILED -2
#define CRAB_ACTION_ERROR_EXEC_FAILED -3

/* Actions */
#define CRAB_ACTION_NO_ACTION 1
#define CRAB_ACTION_EXECUTE 2
#define CRAB_ACTION_EXIT 3
#define CRAB_ACTION_CD 4
#define CRAB_ACTION_PWD 5
#define CRAB_ACTION_COLOUR 6
#define CRAB_ACTION_AD 7
#define CRAB_ACTION_VIEW 8
#define CRAB_ACTION_SETP 9

/* Generates error text for a provided error code
 *
 * error_code - The error code, provided by another crab_action function
 * returns - string containing error message
 */
char *crab_action_error_get_text(int error_code);

/* Reads a command string and determines an action code
 *
 * command - command string to interpret
 * returns - action code
 */
int crab_action_find_action(char *command);

/*  Performs an action based on an action code
 *
 * action - action code
 * argv - argv for action
 * returns - CRAB_ACTION_ERROR_SUCCESS on success, error code otherwise
 */
int crab_action_perform_action(int action, char **argv);

/* Forks to background, execs a program and waits
 *
 * command - program to exec
 * argv - arguments for command
 * returns - CRAB_ACTION_ERROR_SUCCESS on success, error code on error
 */
int crab_action_fork_exec_wait(char *command, char **argv);

#endif
