/*
Brett Kurzawa
CS3141 Team Software Project
2/13/2017
Contains the structure for a basic command history. Will be implemented with a doubly linked list data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *content;
    struct node *last;
    struct node *next;
} Node;

// Instance variables

// Number of elements in the history
int size;
// Current position in the history list
Node *currPos;
// The first node in the list
Node *head;
// The last node in the list
Node *tail;

// Initialize the empty list
extern void init();

// Create a new node with content
extern Node *createNode(Node *last, Node *next, char *content);

// Adds a new command to the end of the history list
extern Node *addLast(char *content);

// Returns the first position in the history list
extern Node *getFirst();

// Returns the last position in the history list
extern Node *getLast();

// Returns the current position in the history list
extern Node *getCurrPos();

// Returns the content of the command in the specified position
extern char *getContent(Node *pos);

// Returns the content of the command in the current position
extern char *getCurrContent();

// Add a new command to the end of the list
extern Node *addCommand();

// Getter and Setter for size
extern int getSize();

extern void setSize();