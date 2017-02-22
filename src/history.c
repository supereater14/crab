#include "history.h"

// List is empty by default so size is 0
int size = 0;

Node* head;
Node* tail;
Node* currPos;

// Initialize the empty list
void init() {
  head = createNode(NULL, NULL, NULL);
  tail = createNode(head, NULL, NULL);
  currPos = tail;
}

Node* createNode(Node* last, Node* next, char* content) {
  Node* newNode = malloc(sizeof(Node));
  newNode->content = content;
  newNode->last = last;
  newNode->next = next;
  size++;
  return newNode;
}

// Adds a node to the end of the list
Node* addLast(char* content) {
  // Add the new node just before the tail
  Node* newNode = createNode(tail->last, tail, content);
  return newNode;
}

// Returns a pointer to the first node in the list
Node* getFirst() {
  return first;
}

// Returns a pointer to the last node in the list
Node* getLast() {
  return last;
}

// Returns the content of the command in the specified position
char* getContent(Node* pos) {
  return pos->content;
}

// Returns the content of the command in the current position
char* getCurrContent() {
  return getContent(currPos);
}

// Adds a command to the end of the list
Node* addCommand(Node* cmd) {
  addLast(cmd);
}

// Return the number of elements in the list
int getSize() {
  return size;
}

// Set the size of the list
void setSize(int s) {
  size = s;
}

int main(int argc, char** argv) {
  addLast("test");
}
