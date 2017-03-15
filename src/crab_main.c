#include "crab.h"
#include "crab_action.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <signal.h>
#include <errno.h>


int main(int argc, char **argv){
  char *buf;
  char **split_buf;
  char **freer_temp;
  char *error_text;
  size_t buf_size;
  size_t size_read;
  int error;
  int action;

  buf_size = 100;

  for(;;){
  ///* Print prompt */
    //if(getuid()){
  //write(1, "$ ", 2);
  //}
  //else{
  //  write(1, "# ", 2);
  //}

    /* Read user input */
    //size_read = read(0, buf, 99);
    //buf[size_read] = '\0';
    buf = readline("$ ");

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
