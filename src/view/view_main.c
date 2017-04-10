#include "ftype.h"
#include "./crab.h"

int setProgram(char* progName, filetype_t fType){
  
  //Value and key to assign to environment variable.
  char string[256];
  
  //Adds the key to the environment variable.
  switch(fType) {
    
  case UNKNOWN:
    break;

  case AUDIO:
    strncat(string, "audio=", 250);
    break;

  case VIDEO:
    strncat(string, "video=", 250);
    break;

  case MEDIA:
    strncat(string, "media=",250);
    break;
      
  case IMAGE:
    strncat(string, "image=",250);
    break;

  case TEXT:
    strncat(string, "text=",250);
    break;

  case DOCUMENT:
    strncat(string, "document=",250);
    break;

  case PRESENTATION:
    strncat(string, "presentation=",250);
    break;

  case SPREADSHEET:
    strncat(string, "spreadsheet=",250);
    break;

  case SOURCE:
    strncat(string, "source=",250);
    break;

  case BINARY:
    strncat(string, "binary=",250);
    break;

  }

  //Sets the given program as the value of the environment
  //variable.
  strncat(string, progName, 250);

  if( putenv(string) != 0 ) {
    exit(1);
  }

}

char* getProgram(filetype_t fType) {

  char string[256];
  char* value = malloc(sizeof(char)*256);

  //Gets the environment variable to retrieve.
  switch (fType) {
  
  case MEDIA:
    strncat(string, "media",250);
    break;
    
  case IMAGE:
    strncat(string, "image",250);
    break;

  case TEXT:
    strncat(string, "text",250);
    break;

  case DOCUMENT:
    strncat(string, "document",250);
    break;

  case PRESENTATION:
    strncat(string, "presentation",250);
    break;

  case SPREADSHEET:
    strncat(string, "spreadsheet",250);
    break;
   
  case SOURCE:
    strncat(string, "source",250);
    break;
   
  case BINARY:
    strncat(string, "binary",250);
    break;

  }
  
  //Gets the value of the env. variable
  strncpy(value, getenv(string), 250);

  if( value == NULL ) {
    exit(1);
  }

  return value;

}

char* getViewCommand(char* filename) {
  
  char* command = malloc(sizeof(char)*512);
  char* program;
  filetype_t type;

  type = get_type_fname(filename);
  
  program = getProgram(type);
  strncat(command, program, 510);
  strncat(command, " ", 510);
  free(program);

  strncat(command, filename, 510);

  return command;
}

