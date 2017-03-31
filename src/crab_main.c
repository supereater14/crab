#include "crab.h"
#include "crab_action.h"
#include "history.h"
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
#include <ncurses.h>


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

  /* Print help message on start if user provided "help" arg */
  if(argc > 1) {
    if(strcmp("help", argv[1]) == 0) {
      write(1, "This will print a help message\n", 31);
    }
  }

  buf_size = 100;

  /* Initialize the command history */
  init();

  for(;;){

//    printf("Testing getch()\n");
//    char* test1 = getch();
//    char* test2 = getch();
//    char* test3 = getch();
//    printf("%c %c %c", test1, test2, test3);
//    readline("Nothin ");
//    /* Check for special character input */
//    for(;;) {
//      char test = getch();
//      printf("%c", getch());
//      printf("%c", getch());
//      readline("");
//      if (getch() == '\033') {
//        // Skip useless info
//        printf("Runs?");
//        getch();
//        printf("%c", getch());
//        readline("");
//        switch(getch()) {
//          case 65:
//            printf("Got up arrow\n");
//            break;
//          case 66:
//            printf("Got down arrow\n");
//            break;
//          case 67:
//            printf("Got left arrow\n");
//            break;
//          case 68:
//            printf("Got right arrow\b");
//            break;
//        }
//      }
//    }
//    /* Get keys as input */
//    char* buffer = malloc(buf_size);
//    int bufLen = 0;
//    initscr();
//    keypad(stdscr, TRUE);
//    for(;;) {
//      int ch;
//
//      ch = getch();
//
//      if (ch == KEY_UP) {
//        up();
//        printf("%s", getCurrContent());
//      }
//      else if (ch == KEY_DOWN) {
//        down();
//        printf("%s", getCurrContent());
//      }
//      else if (ch == 10) {
//        break;
//      }
//      else {
//        char tempch = (char) ch;
//        printf("%c", tempch);
//        buffer[bufLen] = tempch;
//        bufLen++;
//      }
//    }

    /* Behavior immediately after running a history command */
    if (histFlag) {
      char *temp = readline("crab$ ");
      int tempInt = atoi(temp);
      if (tempInt == 0) {
        break;
      }
      buf = getCmdFromHist(tempInt);
      if (!strcmp(buf, "Failed!")) {
        write(2, "Invalid index ", 7);
        continue;
      }
      histFlag = 0;
    }
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
