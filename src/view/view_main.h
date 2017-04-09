#ifndef VIEW_MAIN_H
#define VIEW_MAIN_H

#include "ftype.h"
#include "./crab.h"

/* Sets the default program used for filetype fType.
 *
 * progName - program to be used for give filetype.
 * fType - filetype to assign
 *
 * Returns 0 on normal operation.
 */
int setProgram(char* progName, filetype_t fType);

/* Gets the program used to open the filetype.
 *
 * fType - filetype to be opened.
 *
 * Returns the name of the program to use.
 */
char* getProgram(filetype_t fType);

/* Gets the actual command to execute after view is called.
 *
 * filename - file to "view"
 *
 * Returns the command to use for execution.
 * NOTE: THIS RETURN VALUE IS MALLOC'ED IT MUST BE FREED!
 */
char* getViewCommand(char* filename);

#endif
