// ██████╗  ██╗   ██╗ ██╗ ██╗   ████████╗ ██╗ ███╗   ██╗
// ██╔══██╗ ██║   ██║ ██║ ██║   ╚══██╔══╝ ██║ ████╗  ██║
// ██████╔╝ ██║   ██║ ██║ ██║      ██║    ██║ ██╔██╗ ██║
// ██╔══██╗ ██║   ██║ ██║ ██║      ██║    ██║ ██║╚██╗██║
// ██████╔╝ ╚██████╔╝ ██║ ███████╗ ██║    ██║ ██║ ╚████║
// ╚═════╝   ╚═════╝  ╚═╝ ╚══════╝ ╚═╝    ╚═╝ ╚═╝  ╚═══╝

#include "builtin.h"
#include <unistd.h> // for getcwd, chdir
#include <linux/limits.h> // for PATH_MAX
#include <sys/stat.h> // for stat
#include <string.h>
#include <errno.h>

static char* PIT_DIR = NULL;

// __PIT FINDER__
char* pit_finder(void) {
    char cwd[PATH_MAX];
    struct stat st;

    // Save the original working directory
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("getcwd");
        return NULL;
    }

    while(1) {
        char pit_path[PATH_MAX];
        snprintf(pit_path, sizeof(pit_path), "%s/.pit", cwd);

        // Check if the .pit directory exist 
        if(stat(pit_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            PIT_DIR = malloc(strlen(pit_path) + 1);
            if(PIT_DIR == NULL) {
                perror("malloc");
                return NULL;
            }

            strcpy(PIT_DIR, pit_path); //copy to PIT_DIR
            return PIT_DIR;
        }

        // Check if we reached root directory
        if(strcmp(cwd, "/") == 0) {
            break;
        }

        // Move up a directory
        char* last_slash = strrchr(cwd, '/');
        if(last_slash == NULL) {
            perror("strrchr:last_slash");
            break;
        }
        *last_slash = '\0';

    }

    fprintf(stderr, ".pit directory not found\n");
    return NULL;
}