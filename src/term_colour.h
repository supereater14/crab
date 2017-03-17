#ifndef TERM_COLOUR_H
#define TERM_COLOUR_H

/* Colour codes */
#define TERM_COLOUR_RESET	"\x1b[0m\n"
#define TERM_COLOUR_RED		"\x1B[31m\n"
#define TERM_COLOUR_MAGENTA	"\x1B[35m\n"
#define TERM_COLOUR_YELLOW	"\x1B[33m\n"
#define TERM_COLOUR_GREEN	"\x1B[32m\n"
#define TERM_COLOUR_BLUE	"\x1B[34m\n"
#define TERM_COLOUR_CYAN	"\x1B[36m\n"
#define TERM_COLOUR_WHITE	"\x1B[37m\n"

/* Error codes */
#define TERM_COLOUR_ERROR_SUCCESS 0
#define TERM_COLOUR_ERROR_INVALID_COLOUR_STRING 1

/* Sets the terminal colour
 * Valid colours are:
 * 	reset - resets to default colour
 * 	red
 * 	magenta
 * 	yellow
 * 	green
 * 	blue
 * 	cyan
 * 	white
 *
 * colour - string containing colour to set to
 * returns - TERM_COLOUR_ERROR_SUCCESS on success, error code on error
 */
int term_colour_set_colour(char *colour);

#endif
