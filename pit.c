/**
 * @file pit.c
 * @author Akshai Krishna KP
 * @brief Central point of the entire project.
 * @version 0.1
 * @date 2025-08-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief structure that contain user input and function pointer
 * 
 */
struct pit_cmd {
    const char *cmd_name; // Const value with changable pointer.
    int (*fn)(int , const char**); // Function Pointer.
};

/**
 * @brief Array of the possible command builtin pit.
 * 
 * @details 
 * This global array is called when pit is started. 
 * fun_finder() will match the String and find the corresponding function.
 * Then using function pointer, It will directed to the function.
 * 
 * @note
 * Add the name and function name (cmd_{name}) in this array when add new commands.
 */
static struct pit_cmd cmd[] = {
    {"start", cmd_start},
    {"add", cmd_add},
    {"commit", cmd_commit},
    {"config", cmd_config},
    {"clone", cmd_clone},
    {"status", cmd_status},
    {"log", cmd_log},
    {"branch", cmd_branch},
    {"checkout", cmd_checkout},
    {"merge", cmd_merge},
    {"rebase", cmd_rebase},
    {"push", cmd_push},
    {"pull", cmd_pull},
};

/**
 * @brief 
 * Function will find the function pointer corresponding to the name 
 * user has given.
 * 
 * @details
 * Function take a constant string variable, which was the second word
 * given by user. This must be the command that need to be executed.
 * If will traverse through the cmd[] array to find matching string and 
 * return it's position. Which can be used to get the function pointer 
 * pointing to the needed function.
 * If No match is found NULL is returned.
 * 
 * @param argv 
 * @return struct pit_cmd* 
 */
struct pit_cmd *fun_finder(const char *argv) {
    for(int i=0; i<sizeof(cmd)/sizeof(cmd[0]); i++) {
        struct pit_cmd *p = cmd + i; // same as cmd[i];
        if(!strcmp(argv, p->cmd_name)) 
            return p;
    }
    return NULL;
}

int main(int argc, const char **argv) {
    // Remove the unwanted int and string 
    argc--;
    argv++;

    /**
     * @brief
     * If no argument is given, it will display the help command.
     * 
     */
    if(!argc) {
        cmd = "help";
        return 0;
    }

    /**
     * @brief 
     * Call the fun_finder and get the struct that match the argv
     * This struct also contain a function pointer that point to 
     * the needed function.
     * 
     */
    struct pit_cmd *cmd_struct = fun_finder(argv);
    cmd_struct->fn(argc, argv); // Call the function

    /**
     * @todo Error checkup function and module.
     * 
     */

    return 0;
}