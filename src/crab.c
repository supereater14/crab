#include "crab.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
