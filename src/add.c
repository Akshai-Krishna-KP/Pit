#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "pit_cmd.h"

/**
 * @brief Check if given string is a valid file or dictory path
 * 
 * This function uses stat() system call to determine if a path exists.
 * It's a reliable way to verify if a file or directory exist.
 * 
 * @param path The string that need to verify
 * @return int 1 if exist , 0 otherwise
 */
int is_valid_path(const char *path) {
    struct stat st;
    if(stat(path, &st) == 0) {
        return 1;
    }
    else {
        if(errno == ENOENT) {
            return 0;
        }
        else {
            perror("Error checking path");
            return 0;
        }
    }
}


int cmd_add(int argc, const char **argv) {
    // Check if the number of argumnent is correct.
    if(argc != 2) {
        return 30;
    }

    // Check the argument is a valid pathway.
    if(!is_valid_path(*(++argv))) {
        return 31;
    }
}