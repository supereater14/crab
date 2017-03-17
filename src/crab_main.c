#include "crab.h"
#include "crab_action.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
  char *buf;
  char **split_buf;
  char **freer_temp;
  char *error_text;
  size_t buf_size;
  size_t size_read;
  int error;
  int action;

  /* Print help message on start if user provided "help" arg */
  if(argc > 1) {
    if(strcmp("help", argv[1]) == 0) {
      write(1, "This will print a help message\n", 31);
    }
  }

  buf_size = 100;
  buf = malloc(buf_size * sizeof(char));

  for(;;){
    /* Print prompt */
    if(getuid()){
      write(1, "crab$ ", 6);
    }
    else{
      write(1, "crab# ", 6);
    }

    /* Read user input */
    size_read = read(0, buf, 99);
    buf[size_read] = '\0';

    /* Handle piped commands */
    if(crab_isPiped(buf)) {
      error = crab_split_exec_piped_command(buf);
      if(error != CRAB_ACTION_ERROR_SUCCESS) {
        error_text = crab_action_error_get_text(error);
        write(2, "Error: ", 7);
        write(2, error_text, strlen(error_text));
        write(2, "\n", 1);
        return -1;
      }
      continue;
    }

    /* Split the command string */
    error = crab_split_command_string(buf, &split_buf);
    if(error != CRAB_ACTION_ERROR_SUCCESS){
      error_text = crab_action_error_get_text(error);
      write(2, "Error: ", 7);
      write(2, error_text, strlen(error_text));
      write(2, "\n", 1);
      return -1;
    }

    /* Find action code */
    action = crab_action_find_action(split_buf[0]);

    /* Perform action */
    error = crab_action_perform_action(action, split_buf);
    if(error != CRAB_ACTION_ERROR_SUCCESS){
      error_text = crab_action_error_get_text(error);
      write(2, "Error: ", 7);
      write(2, error_text, strlen(error_text));
      write(2, "\n", 1);
      return -1;
    }

    /* Free split buffer */
    freer_temp = split_buf;
    while(*split_buf != NULL){
      free(*split_buf);
      split_buf++;
    }
    free(freer_temp);
  }

  return 0;
}
