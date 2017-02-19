#include <history.h>

// List is empty by default so size is 0
size = 0;
// Command history is empty by default
currPos = NULL;
first = currPos;
last = currPos;

Node* createNode(Node* last, Node* next, string content) {
  Node newNode = malloc(sizeof(Node));
  newNode->content = content;
  newNode->last = last;
  newNode->next = next;
  size++;
  return newNode;
}

// Adds a node to the end of the list
Node* addLast(Node* last, string content) {
  Node newLast = createNode(last, NULL, content);
  last->next = newLast;
  last = newLast;
  return last;
}

// Returns a pointer to the first node in the list
Node* first() {
  return first;
}

// Returns a pointer to the last node in the list
Node* last() {
  return last;
}

// Returns the content of the command in the specified position
string getContent(Node* pos) {
  return pos->content;
}

// Returns the content of the command in the current position
string getCurrContent() {
  return getContent(currPos);
}

// Return the number of elements in the list
int size() {
  return size;
}

// Set the size of the list
void setSize(int s) {
  size = s;
}
