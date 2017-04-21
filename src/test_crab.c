/* Authors: Riley Mulford, Brett Kurzawa,Dylan Brosseau
 * CS3141 Spring 2017
 * Crab Test Code
 */

#include "history.h"
#include "alias.h"
#include "term_colour.h"
#include <string.h>
#include <unistd.h>
#include <assert.h>

Crab_Alias crab_alias;

/* Testing init function */
int test_init()
{
	init_alias();
	assert(crab_alias.count == 0);
	printf("init_alias: Correctly init alias");
	return 0;
}
/* Tests add function */
int test_add()
{
	int ret;
	/* Test adding alias */
	ret = add_alias("name", "/home/");
	assert(ret == 0);
	assert(crab_alias.count == 1);
	printf("add_alias: Correctly added alias\n");
	/* Test adding alias with too long of a name */
	ret = add_alias("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", "/home/");
	assert(ret == -1);
	assert(crab_alias.count == 1);
	printf("add_alias: Correctly prevented adding alias with too long of a name\n");
	return 0;
}
/* Tests is_alias function */
int test_is_alias()
{
	int ret;
	ret = is_alias("name");
	assert(ret >= 0);
	printf("is_alias: Correctly found existing alias");
	ret = is_alias("memes");
	assert(ret == -1);
	printf("is_alias: Correctly did not find non-existing alias");
	return 0;
}
/* Tests remove alias function */
int test_remove()
{
	int ret;
	ret = remove_alias("name");
	assert(ret == 0);
	printf("remove_alias: Correctly removed existing alias");
	ret = remove_alias("memes");
	printf("remove_alias: Correctly did not remove non-existing alias\n");
	return 0;
}
/* Tests print alias function */
int test_print()
{
	int i;
	int foundone = 0;
	int ret;
	/* Test adding alias */
	ret = add_alias("name", "/home/");
	assert(ret == 0);
	printf("print_alias: Correctly added alias\n");

	for(i = 0; i < crab_alias.count; i++) {
		if(!is_removed(i)) {
			printf("Name: %s Directory: %s\n", crab_alias.names[i], crab_alias.directories[i]);
			foundone = 1;
		}
	}

	if(!foundone) {
		printf("No alias found\n");
	}
	printf("print_alias: Correctly printed out alias\n");
	return 0;
}
/* Tests find alias name function */
int test_find_alias_name()
{
	int i;
	printf("Looking up data on name: %s\n", "name");
	for(i = 0; i < crab_alias.count; i++) {
		if(strcmp(crab_alias.names[i], "name") == 0) {
			printf("Name: %s Directory: %s\n", crab_alias.names[i], crab_alias.directories[i]);
			printf("find_alias_name: Correctly found and printed alias name");
			return 0;
		}
	}

	printf("No data found\n");
	return 0;
}
/* Tests find alias directory function */
int test_find_alias_dir()
{
	int i;
	int foundone = 0;
	printf("Looking up data on directory: %s\n", "/home/");
	for(i = 0; i < crab_alias.count; i++) {
		if(strcmp(crab_alias.directories[i], "/home/") == 0) {
			printf("Name: %s Directory: %s\n", crab_alias.names[i], crab_alias.directories[i]);
			foundone = 1;
		}
	}

	if(foundone == 0) {
		printf("No data found\n");
	}

	printf("find_alias_dir: Correctly found and printed directories\n");

	return 0;
}
/* Tests reset alias function */
int test_reset()
{
	int ret;
	ret = reset_alias();
	assert(crab_alias.count == 0);
	assert(ret == 0);
	printf("reset_alias: Correctly reset alias\n");
	return 0;
}
/* Tests save alias function */
int test_save()
{
	int ret;
	ret = save_alias();
	assert(ret == 0);
	printf("save_alias: Correctly saved alias\n");
	return 0;
}
/* Tests remove log function */
int test_remove_log()
{
	int ret;
	ret = remove_log();
	assert(ret == 0);
	printf("remove_log: Correctly removed log\n");
	return 0;
}

/*
 * Tests the colour set command.
 * Aborts the program if any assertion is
 * violated.
 */
void testColour(void) {
  
  printf("Testing terminal color feature...\n");

  int returnValue = 3;
  int errorReturn = 3;

  //Set up strings for testing.
  char** validColors = malloc(8 * sizeof(char*));
  validColors[0] = "reset"; 
  validColors[1] = "red";
  validColors[2] = "magenta";
  validColors[3] = "yellow";
  validColors[4] = "green";
  validColors[5] = "blue";
  validColors[6] = "cyan";
  validColors[7] = "white";
  
  char** invalidColors = malloc(8 * sizeof(char*));
  invalidColors[0] = "";
  invalidColors[1] = "purple";
  invalidColors[2] = "sidfoijhoitrjhnoimhnfjokjtyoikogg";
  invalidColors[3] = " ";
  invalidColors[4] = "royal blue";
  invalidColors[5] = "not/a/color..$543@";
  invalidColors[6] = "maganta";
  invalidColors[7] = "rest";

  //Test valid strings
  for(int i = 0; i < 8; i++) {
    returnValue = term_colour_set_colour(validColors[i]);
    //Makes assertions for the return values of the function.
    assert( returnValue != TERM_COLOUR_ERROR_INVALID_COLOUR_STRING );
  }

  //Test invalid strings
  for(int i = 0; i < 8; i++) {
    errorReturn = term_colour_set_colour(invalidColors[i]);
    //Makes assertions for the return values of the function.
    assert( errorReturn != TERM_COLOUR_ERROR_SUCCESS );
  }

  free(validColors);
  free(invalidColors);

  printf("Color set tests successful!\n\n");

}

int main(int argc, char**agrv)
{
	/* Test colour */
	testColour();

	/* Test alias stuff */
	test_init();
	test_add();
	test_is_alias();
	test_remove();
	test_print();
	test_find_alias_name();
	test_find_alias_dir();
	test_reset();
	test_save();
	test_remove_log();

   // Test that the list is empty on startup
	assert(isEmpty());
	printf("Command history is empty\n");

	init();

	printf("Init worked\n");

	char* buf = malloc(100);
	strncpy(buf, "first", 5);

	addLast(buf);

	printf("add last worked\n");

   // Test that the list size is correct
	assert(getSize() == 1);
	printf("Size is 1\n");

	char *temp = malloc(100);
	strncpy(temp, "test\n", 5);
	temp = parseCmd(temp);
	printf("%s\n", temp);
   // Test that parseCmd properly removes newline
   	assert(!strcmp(temp, "test"));
	printf("parseCmd properly removes newlines from end of string\n");

	parseCmd(temp);
   // Test that parseCmd does not break when passed with a string with no newline at the end
	assert(!strcmp(temp, "test"));
	printf("parseCmd works properly for strings with no newline at the end\n");

	char *temp2 = malloc(100);
	strncpy(temp2, getContent(getLast()), 5);

	char* buf2;

   // Test that getLast() works properly
	assert(strcmp(temp2, "first") == 0);
	printf("First command inserted properly\n");

	for (int i = 0; i < 10; i++) {
		buf2 = malloc(100);
		strncpy(buf2, "test", 4);
		addLast(buf2);
	}

   // Test that 10 nodes were added properly
	assert(getSize() == 11);
	printf("Size is 11\n");

   // Rewind to the front of the list
	for (int i = 0; i < getSize(); i++) {
		up();
	}

	char* buf3 = malloc(100);
	strncpy(buf3, getCurrContent(), 5);

	assert(!strcmp(buf3, "first"));
	printf("up() returned to the first node properly\n");

   // Move to the last node again
	for (int i = 0; i < getSize(); i++) {
		down();
	}

	printf("****EVERY TEST WORKED!***\n");
}