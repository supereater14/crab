/******************************************
Author: Riley Mulford
CS3141 Team Software
3/29/2017
Alias for crabshell
******************************************/

#include "alias.h"

Crab_Alias crab_alias;

int init_alias()
{
    int i;
    /*
    FILE* fid;
    char name_buf[MAXALIASLENGTH];
    char dir_buf[MAXALIASLENGTH];
    */

    /* Set memory */
    for(i = 0; i < MAXALIAS; i++) {
        memset(crab_alias.names[i], (char)0, MAXALIASLENGTH);
        memset(crab_alias.directories[i], (char)0, MAXALIASLENGTH);
    }
    crab_alias.count = 0;

    /* open alias log
    fid = fopen("alias.log", O_RDONLY);
    if(fid < 0) {
        perror("open");
        return -1;
    }
    Read name and dir, add alias to session list
    for(i = 0; i < MAXALIAS; i++) {
        fgets(name_buf, MAXALIASLENGTH, fid);
        fgets(dir_buf, MAXALIASLENGTH, fid);
        if(!is_alias(name_buf)) {
            add_alias(name_buf, dir_buf);
        }
    }
    */

    return 0;
}

int add_alias(char* name, char* directory)
{
    int i;
    int openslot = 0;
    int foundat;

    /* check for exceeded bounds */
    if(strlen(name) > MAXALIASLENGTH) {
        printf("Max alias name length exceeded!\n");
        return -1;
    }
    if(crab_alias.count > MAXALIAS) {
        printf("Max alias count exceeded!\n");
        return -1;
    }

    /* See if alias already exists */
    if((foundat = is_alias(name)) >= 0) {
        strcpy(crab_alias.directories[foundat], directory);
        printf("Alias for %s set to name %s\n", directory, name);
        return 0;
    }

    /* Find open slot in array if there is one */
    for(i = 0; i < crab_alias.count; i++) {
        if(!is_removed(i))
            continue;
        openslot = 1;
        strcpy(crab_alias.names[i], name);
        strcpy(crab_alias.directories[i], directory);
        crab_alias.count++;
        printf("Alias for %s set to name %s\n", directory, name);
        return 0;
    }

    /* If no holes in array, just add to the end */
    if(!openslot) {
        strcpy(crab_alias.names[crab_alias.count], name);
        strcpy(crab_alias.directories[crab_alias.count], directory);
        crab_alias.count++;
        printf("Alias for %s set to name %s\n", directory, name);
        return 0;
    }

    return -1;
}

int is_alias(char* name)
{
    int i;
    for(i = 0; i < crab_alias.count; i++) {
        /* Name found */
        if(strcmp(crab_alias.names[i], name) == 0) {
            return i;
        }
    }
    /* Name not found */
    return -1;
}

int remove_alias(char* name)
{
    int foundat;
    if((foundat = is_alias(name)) >= 0) {
        printf("Removed alias: %s assigned to directory: %s\n", crab_alias.names[foundat], crab_alias.directories[foundat]);
        memset(crab_alias.names[foundat], (char)0, MAXALIASLENGTH);
        memset(crab_alias.directories[foundat], (char)0, MAXALIASLENGTH);
        return 0;
    }
    printf("Unable to remove alias: %s (alias might not exist)\n", name);
    return -1;
}

int is_removed(int pos)
{
    int i;
    for(i = 0; i < MAXALIASLENGTH; i++) {
        if(crab_alias.names[pos][0] != (char)0) {
            return 0;
        }
    }
    return 1;
}

int print_alias()
{
    int i;
    int foundone = 0;
    for(i = 0; i < crab_alias.count; i++) {
        if(!is_removed(i)) {
            printf("Name: %s Directory: %s\n", crab_alias.names[i], crab_alias.directories[i]);
            foundone = 1;
        }
    }

    if(!foundone) {
        printf("No alias found\n");
    }
    return 0;
}

int reset_alias()
{
    int i;
    /* Zero out memory */
    for(i = 0; i < MAXALIAS; i++) {
        memset(crab_alias.names[i], (char)0, MAXALIASLENGTH);
        memset(crab_alias.directories[i], (char)0, MAXALIASLENGTH);
    }
    crab_alias.count = 0;

    printf("alias list reset\n");

    return 0;
}

int save_alias()
{
    int i;
    int fid;

    /* open log file */
    fid = open("alias.log", O_WRONLY | O_CREAT | O_APPEND, 0640);
    if(fid < 0) {
        perror("open");
        return -1;
    }

    /* Write alias list to file */
    for(i = 0; i < crab_alias.count; i++) {
        if(!is_removed(i)) {
            write(fid, crab_alias.names[i], strlen(crab_alias.names[i]));
            write(fid, "\n", 1);
            write(fid, crab_alias.directories[i], strlen(crab_alias.directories[i]));
            write(fid, "\n", 1);
        }
    }

    close(fid);

    return 0;
}

int remove_log()
{
    remove("alias.log");
    return 0;
}

char* get_dir(int pos)
{
    return crab_alias.directories[pos];
}

int find_alias_name(char* name)
{
    int i;
    printf("Looking up data on name: %s\n", name);
    for(i = 0; i < crab_alias.count; i++) {
        if(strcmp(crab_alias.names[i], name) == 0) {
            printf("Name: %s Directory: %s\n", crab_alias.names[i], crab_alias.directories[i]);
            return 0;
        }
    }

    printf("No data found\n");
    return 0;
}
int find_alias_dir(char* directory)
{
    int i;
    int foundone = 0;
    printf("Looking up data on directory: %s\n", directory);
    for(i = 0; i < crab_alias.count; i++) {
        if(strcmp(crab_alias.directories[i], directory) == 0) {
            printf("Name: %s Directory: %s\n", crab_alias.names[i], crab_alias.directories[i]);
            foundone = 1;
        }
    }

    if(foundone == 0) {
        printf("No data found\n");
    }

    return 0;
}

int print_alias_help()
{
    printf("Set an alias with ad (see commands below) and cd to that alias\n");
    printf("cmds:\n");
    printf("ad - 0 args - sets alias [prev] equal to current directory\n");
    printf("ad [name]- 1 args - sets alias [name] equal to current directory\n");
    printf("ad [name] [dir] - 2 args - sets alias [name] equal to [dir]\n");
    printf("ad print - print all alias\n");
    printf("ad findn [name] - print directory associated with [name]\n");
    printf("ad findd [dir] - print names associated with [dir]\n");
    printf("ad save - save all alias to file to be used in other sessions\n");
    printf("ad deletelog - delete alias.log and its contents\n");
    printf("ad reset - reset all alias for this current session\n");
    printf("cd [name] - change directory to the directory corresponding to [name]\n");
    return 0;
}
