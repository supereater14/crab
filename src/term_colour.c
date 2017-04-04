#include "term_colour.h"
#include <string.h>
#include <unistd.h>

int term_colour_set_colour(char *colour){
	if(!strcmp(colour, "reset")){
		write(1, TERM_COLOUR_RESET, 6);
	}
	else if(!strcmp(colour, "red")){
		write(1, TERM_COLOUR_RED, 7);
	}
	else if(!strcmp(colour, "magenta")){
		write(1, TERM_COLOUR_MAGENTA, 7);
	}
	else if(!strcmp(colour, "yellow")){
		write(1, TERM_COLOUR_YELLOW, 7);
	}
	else if(!strcmp(colour, "green")){
		write(1, TERM_COLOUR_GREEN, 7);
	}
	else if(!strcmp(colour, "blue")){
		write(1, TERM_COLOUR_BLUE, 7);
	}
	else if(!strcmp(colour, "cyan")){
		write(1, TERM_COLOUR_CYAN, 7);
	}
	else if(!strcmp(colour, "white")){
		write(1, TERM_COLOUR_WHITE, 7);
	}
	else{
		return TERM_COLOUR_ERROR_INVALID_COLOUR_STRING;
	}

	return TERM_COLOUR_ERROR_SUCCESS;
}
