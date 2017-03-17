#ifndef CRAB_H
#define CRAB_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

/* Error return values */
#define CRAB_ERROR_UNMATCHED_QUOTE -1
#define CRAB_ERROR_FORK_FAILED -2
#define CRAB_ERROR_EXEC_FAILED -3
#define CRAB_ERROR_DUP_FAILED -4

#define MAXCMDLENGTH 120
#define MAXCMDS       20
#define MAXARGS       20

struct command
{
  const char** cmdstr;
};

/* Splits a command string into arguments
 * THIS FUNCTION MALLOCS
 *
 * command_string - The complete command string
 * argv - Generated argv from command string
 * returns - 0 on success, nonzero on failure
 */
int crab_split_command_string(char *command_string, char ***argv);

/* Checks a command string for any | characters
 *
 * command_string - the complete command string
 */
int crab_isPiped(char *command_string);

/* Splits a command string based on pipe characters
 * Executes any number of piped commands
 * 
 * command_string - the complete command string
 * argv - generated argv from command string
 */
int crab_split_exec_piped_command(char* command_string);

/*
fork-execs any number of piped commands (or just one command)
params: number of commands, command structure
returns ret result from execvp - (errors handled by caller)
*/
int fork_pipes (int n, struct command *cmd);

/*
Spawn procedures for each command
params: in fd, out fd, command structure
returns: process ID
*/
int spawn_proc (int in, int out, struct command *cmd);

#endif
