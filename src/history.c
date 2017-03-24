#include "history.h"

// List is empty by default so size is 0
int size = 0;

Node *last;
Node *currPos;

// Initialize the list
void init() {
    last = createNode(NULL);
    last->prev = NULL;
    currPos = last;
    buildHist();
}

// Build the command history from stored file
void buildHist() {
    // Opens the cmdhist.txt file if it exists, or creates a new one
    FILE *hist = fopen("cmdhist.txt", "a+");
    char *cmd;
    // Retrieve command history from file and add to the active session's history
    while(fgets(cmd = malloc(sizeof(char)*255), sizeof(cmd), hist)) {
        addLast(cmd);
    }

    // Close the file
    fclose(hist);
}

// Returns true if empty, false otherwise
bool isEmpty() {
    return getSize() == 0;
}

// Creates a new node containing the specified string and pointing to the
// specified nodes
Node *createNode(char *content) {
    Node *newNode = malloc(sizeof(Node));
    newNode->content = content;
    return newNode;
}
// debug
int count = 0;
// Adds a node to the end of the list
Node *addLast(char *content) {
    // If the list is empty newNode becomes last, else newNode is added after last
    Node *newNode = createNode(content);
    if (isEmpty()) {
        last->prev = newNode;
    }
    else {
        newNode->prev = last->prev;
        newNode->next = last;
        last->prev = newNode;
    }
    size++;

    return newNode;
}

// Returns a pointer to the last node in the list
Node *getLast() {
    return last->prev;
}

// Returns the content of the command in the specified position
char *getContent(Node *pos) {
    return pos->content;
}

// Returns the content of the command in the current position
char *getCurrContent() {
    return getContent(currPos);
}

// Adds a command to the end of the list
Node *addCommand(char *cmd) {
    // Open file for writing
    FILE *hist = fopen("cmdhist.txt", "a");

    // Add the command to the end of the list
    Node *temp = addLast(cmd);

    // Write the command to the end of the file
    fprintf(hist, "%s\n", getContent(temp));

    // Close the file
    fclose(hist);

    return temp;
}

// Return the number of elements in the list
int getSize() {
    return size;
}

// Set the size of the list
void setSize(int s) {
    size = s;
}

int main(int argc, char **argv) {
    init();
    if (isEmpty()) {
        addCommand("Test1");
        addCommand("Test2");
        addCommand("Test3");
        addCommand("Test4");
        init();
    }
    printf("Checkin1\n");
    currPos = getLast();
    printf("Checkin2\n");
    while (currPos != NULL) {
        printf("%s", getCurrContent());
        currPos = currPos->prev;
        printf("Checkinloop\n");
    }
    addCommand("Test Add");
    addCommand("Sneaky malicious test\n");
}
