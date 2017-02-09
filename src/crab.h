#ifndef CRAB_H
#define CRAB_H

/* Error return values */
#define CRAB_ERROR_UNMATCHED_QUOTE -1

/* Splits a command string into arguments
 * THIS FUNCTION MALLOCS
 *
 * command_string - The complete command string
 * argv - Generated argv from command string
 * returns - 0 on success, nonzero on failure
 */
int crab_split_command_string(char *command_string, char ***argv);

#endif
