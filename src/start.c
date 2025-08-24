/**
 * @file start.c
 * @author Akshai Krishna KP
 * @brief This file will be basic equivalent to init in git.
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/stat.h>

#include "pit_cmd.h"

/**
 * @brief Ensures that a directory exists at the given path.
 * 
 * This function checks if the specified path exists and is a directory. 
 * - If the directory already exists, it returns 0.
 * - If the path exists but is not a directory, it prints an error and returns 1.
 * - If the directory does not exist, it attempts to create it with permissions 0755.
 *   - On success, returns 0.
 *   - On failure (e.g., permission denied, invalid path), prints the error and returns 1.
 * 
 * @param path The path to the directory to be ensured.
 * @return int Returns 0 on success, 1 on failure.
 */
int dir_create(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) return 0;
        fprintf(stderr, "Path exists but is not a directory: %s\n", path);
        return 1;
    }
    if (mkdir(path, 0755) == -1) {
        perror("mkdir failed");
        return 1;
    }
    return 0;
}

/**
 * @brief Create a config file in the pit repo dir.
 * 
 * This will make a config file which will contain essential info about the repository.
 * 
 * @todo
 * This function has buffer size of 50 for name and 100 for email. If 
 * this limit is exceeded there will be buffer overflow and a security risk.
 * 
 * @param path The path to file to be created.
 * @return int Return 0 if success and 1 if error occured
 */
int file_config(const char *pit_dir) {
    // get the actual pathway
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/config", pit_dir);

    // Create Config file
    FILE *config_file = fopen(full_path, "w");
    if(!config_file) {
        perror("fopen failed");
        return 1;
    }

    /**
     * @details 
     * Unlike git, i am not trying to put user details into a global file. but on a local.
     * Each folder will have a config file which contain their user details.
     * 
     */
    char name[50];
    printf("name: ");
    if(!fgets(name, sizeof(name), stdin)) {
        fprintf(stderr, "Failed to read name\n");
        fclose(config_file);
        return 1;
    }
    name[strcspn(name, "\n")] = 0;

    char email[100];
    printf("email: ");
    if (!fgets(email, sizeof(email), stdin)) {
        fprintf(stderr, "Failed to read email\n");
        fclose(config_file);
        return 1;
    }
    email[strcspn(email, "\n")] = 0;

    /// Check if name and email is not empty
    if (strlen(name) == 0 || strlen(email) == 0) {
        fprintf(stderr, "name or email cannot be empty\n");
        return 1;
    }

    // Add content to config file
    fprintf(config_file,
        "[core]\n"
        "\tfilemode = true\n"
        "\tbare = false\n"
        "[user]\n"
        "\tname = %s\n"
        "\temail = %s\n",
        name, email);

    fclose(config_file);
    return 0;
}

/**
 * @brief Create HEAD file in the .pit dir
 * 
 * This will point to the current working branch.
 * 
 * @param pit_dir 
 * @return int 
 */
int file_head(const char *pit_dir) {
    // Get actual path to file
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/HEAD", pit_dir);

    // Make file and insert the content
    FILE *head = fopen(full_path, "w");
    if(!head) {
        perror("fopen failed");
        return 1;
    }
    fputs("ref: refs/heads/main\n", head);
    fclose(head);

    return 0;
}

/**
 * @brief Main Function in this file
 * 
 * @details
 * This will check if .pit dir exist and if it does return already repo exist.
 * If doesn't exist create a .pit dir and it content:-
 * DIRECTORY ::
 * - branches/
 * - objects/
 * - refs/
 * - refs/heads/
 * FILE ::
 * - config
 * - HEAD
 * 
 * @param argc number of arguments
 * @param argv the arguments
 * @return int 
 */
int cmd_start(int argc, const char **argv) {

    ///@todo Check whether .pit already exist

    // Declare the pit dir and subdir
    const char *pit_dir = ".pit"; ///< Base PIT directory
    const char *subdir_name[] = {"branches", "objects", "refs", "refs/heads"};
    const int NUMBER_OF_SUBDIR = 4;

    // Create Pit dir
    dir_create(pit_dir);

    // Create subdir
    char full_path[256];
    for(int i=0; i<NUMBER_OF_SUBDIR; i++) {
        snprintf(full_path, sizeof(full_path), "%s/%s", pit_dir, subdir_name[i]);
        dir_create(full_path);
    }

    // create Config file
    if(file_config(pit_dir)) {
        perror("file_config");
        return 1;
    }

    // create HEAD file
    if(file_head(pit_dir)) {
        perror("file_head");
        return 1;
    }

    return 0;
}