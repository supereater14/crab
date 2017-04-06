/*
Brett Kurzawa
CS3141 Team Software Project
2/13/2017
Contains the structure for a basic command history. Implemented with a doubly linked list data structure.
Reads stored history from a text file, and stores history during each session.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


#define DISPLAY_HISTORY_ERROR_SUCCESS 0
#define CRAB_HISTORY_OUT_OF_BOUNDS_ERROR 1

typedef struct node {
    char *content;
    struct node *prev;
    struct node *next;
} Node;

// Instance variables

// Number of elements in the history
int size;
// Current position in the history list
Node *currPos;
// The last node in the list
Node *tail;

// Initialize the empty list
extern void init();

// Returns true if empty, false otherwise
extern bool isEmpty();

// Create a new node with content
extern Node *createNode(char *content);

// Adds a new command to the end of the history list
extern Node *addLast(char *content);

// Returns the last position in the history list
extern Node *getLast();

// Returns the current position in the history list
extern Node *getCurrPos();

// Returns the content of the command in the specified position
extern char *getContent(Node *pos);

// Returns the content of the command in the current position
extern char *getCurrContent();

// Add a new command to the end of the command history file
extern Node *addCommand(char *cmd);

// Traverse up in the history
extern void *up();

// Traverse down in the history
extern void *down();

// Print out the specified number of commands
extern int displayHist(int numCommands);

// Create a temp array
extern void makeTempArray(int numCommands);

// Free the temp array
extern void freeTempArray();

// Free the history list
extern void freeHistory();

// Retrieve a command from the temp array
extern char *getCmdFromHist(int index);

// Remove newline at end of string
extern char *parseCmd(char* command);

// Getter and Setter for size
extern int getSize();
extern void setSize();

// Builds the history from stored file
extern void buildHist();