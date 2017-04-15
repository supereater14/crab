#include "crab.h"
#include "crab_action.h"
#include "history.h"
#include "alias.h"
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
  bool histFlag = 0;

  buf_size = 100;
  /* Initialize the command history */
  init();

  init_alias();

  for(;;){

    /* Behavior immediately after running a history command */
    if (histFlag) {
      char *temp = readline("crab$ ");
      int tempInt = atoi(temp);
      free(temp);
      if (tempInt == 0) {
        write(2, "Invalid index\n", 14);
        histFlag = 0;
        continue;
      }
      else {
        // Adjust for offset
        tempInt -= 1;
      }
      buf = malloc(sizeof(char)*buf_size);
      strcpy(buf, getCmdFromHist(tempInt));
      if (!strcmp(buf, "Failed!")) {
        write(2, "Invalid index\n", 14);
        histFlag = 0;
        continue;
      }
      histFlag = 0;
    }
    /* Normal behavior, not directly after history command */
    else {
      /* Read user input */
      //size_read = read(0, buf, 99);
      //buf[size_read] = '\0';
      buf = readline("crab$ ");
    }
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

    /* Add the command to the command history*/
    addCommand(buf);
    /* Set histFlag to true for next loop if history command was called */
    if (!strncmp(buf, "history", 7)) {
      histFlag = 1;
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
