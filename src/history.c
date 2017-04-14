#include "history.h"

// List is empty by default so size is 0
int size = 0;

char **tempArray;
int tempArraySize = 0;
Node *last;
Node *currPos;
int charLength = 100;

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
    char *temp = fgets(cmd = malloc(sizeof(char)*charLength), sizeof(char)*charLength, hist);
    // Retrieve command history from file and add to the active session's history
    while(temp) {
        addLast(parseCmd(cmd));
        temp = fgets(cmd = malloc(sizeof(char)*charLength), sizeof(char)*charLength, hist);
    }
    free(cmd);
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

// Adds a node to the end of the list
Node *addLast(char *content) {
    // Append newline to the end of the command
    char *contentN = strcat(content, "\n");
    // If the list is empty newNode becomes last, else newNode is added after last
    Node *newNode = createNode(contentN);
    if (isEmpty()) {
        last->prev = newNode;
        newNode->next = last;
    }
    else {
        newNode->prev = last->prev;
        newNode->next = last;
        last->prev->next = newNode;
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

    cmd = parseCmd(cmd);

    // Add the command to the end of the list
    Node *temp = addLast(cmd);

    // Write the command to the end of the file
    fprintf(hist, "%s\n", parseCmd(cmd));

    // Close the file
    fclose(hist);

    return temp;
}

// Traverse up in the history
void *up() {
    if (currPos->prev != NULL) {
        currPos = currPos->prev;
    }
    else {
        printf("Reached the front of the list\n");
    }
}

// Traverse down in the history
void *down() {
    if (currPos->next != NULL) {
        currPos = currPos->next;
    }
    else {
        printf("Reached the bottom of the list\n");
    }
}

// Print out the specified number of commands
int displayHist(int numCommands) {
    if (numCommands > getSize()) {
        numCommands = getSize();
    }
    // Rewind to the earliest command to be printed
    int i = 0;
    for (i; i < numCommands; i++) {
        up();
    }

    // Create a temp array to be used to access old commands,
    // and print commands out to the screen
    makeTempArray(numCommands);
    return DISPLAY_HISTORY_ERROR_SUCCESS;
}

// Create a temp array and print out commands to the console
// Along with their indices
void makeTempArray(int numCommands) {
    free(tempArray);
    tempArray = malloc(sizeof(char) * charLength * numCommands);
    tempArraySize = numCommands;
    char *temp;
    // Fast forward back through the history to the end and
    // fill the temp array with the proper commands and
    // indices
    int i = 0;
    for (i; i < numCommands; i++) {
        tempArray[i] = getCurrContent();
        temp = parseCmd(getCurrContent());
        printf("[%d] %s\n", (i + 1), temp);
        down();
    }
}

// Free the temp array
void freeTempArray() {
    free(tempArray);
    tempArraySize = 0;
}

// Free the history list
void freeHistory() {
    currPos = last;
    while (currPos->prev != NULL) {
        Node *temp = currPos;
        up();
        free(temp->content);
        free(temp);
    }
    free(currPos->content);
    free(currPos);
}

// Retrieve a command from the temp array
extern char *getCmdFromHist(int index) {
    if (index < 0 || index > tempArraySize) {
        return "Failed!";
    }
    return tempArray[index];
}

// Remove newline at end of string
extern char *parseCmd(char* command) {
    command = strtok(command, "\n");
    return command;
}

// Return the number of elements in the list
int getSize() {
    return size;
}

// Set the size of the list
void setSize(int s) {
    size = s;
}

//int main(int argc, char **argv) {
//    init();
//    if (isEmpty()) {
//        addCommand("Test1");
//        addCommand("Test2");
//        addCommand("Test3");
//        addCommand("Test4");
//        init();
//    }
//    printf("Checkin1\n");
//    currPos = getLast();
//    printf("Checkin2\n");
//    while (currPos != NULL) {
//        printf("%s", getCurrContent());
//        currPos = currPos->prev;
//        printf("Checkinloop\n");
//    }
//    addCommand("Test Add");
//    addCommand("Sneaky malicious test\n");
//}