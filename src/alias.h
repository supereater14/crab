/******************************************
Author: Riley Mulford
CS3141 Team Software
3/29/2017
Alias for crabshell
******************************************/

#ifndef ALIAS_H
#define ALIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXALIASLENGTH 120
#define MAXALIAS 128

typedef struct crab_alias {
    char directories[MAXALIAS][MAXALIASLENGTH];
	char names[MAXALIAS][MAXALIASLENGTH];
	int count;
} Crab_Alias;

/*
 * Prints out a help page for ad listing all commands
 */
extern int print_alias_help();

/*
 * Reads alias from alias file into alias list
 * Zeros out memory in alias list
 * TODO: Read alias from alias file
 */
extern int init_alias();

/*
 * Adds an alias to the alias list
 * If name already exists, old entry for name is overwritten
 */
extern int add_alias(char* name, char* directory);

/*
 * Checks to see if the provided alias exists in the list
 * Returns the pos in list or -1 if not found
 */
extern int is_alias(char* name);

/*
 * Removes alias listing from alias list
 * If alias name is not valid, does nothing
 */
extern int remove_alias(char* name);

/*
 * Checks a position in the list to see if an alias exists there or not
 */
extern int is_removed(int pos);

/*
 * Prints all valid alias to stdout
 */
extern int print_alias();

/*
 * Resets alias list to defualt state (no alias)
 */
extern int reset_alias();

/*
 * Writes all alias in alias list to a file to be used in future sessions
 * TODO: everything
 */
extern int save_alias();

/*
 * Delete alias log file
 */
extern int remove_log();

/*
 * Find name of the directory at the given position in alias list
 */
extern char* get_dir(int pos);

/*
 * Prints all data associated with given alias name
 */
extern int find_alias_name(char* name);

/*
 * Prints all data associated with given directory name
 */
extern int find_alias_dir(char* directory);

#endif
