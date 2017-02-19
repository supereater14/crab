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
  string content;
  struct node* last;
  struct node* next;
} Node;

// Instance variables

// Number of elements in the history
int size;
// Current position in the history list
Node* currPos;
// The first node in the list
Node* first;
// The last node in the list
Node* last;

// Create a new node with content
Node* createNode(string content);
// Adds a new command to the end of the history list
Node* addLast(Node* first, string content);
// Returns the first position in the history list
Node* first();
// Returns the last position in the history list
Node* last();
// Returns the current position in the history list
Node* currPos();
// Returns the content of the command in the specified position
string getContent(Node* pos);
// Returns the content of the command in the current position
string getCurrContent();
// Getter and Setter for size
int size();
void setSize();
