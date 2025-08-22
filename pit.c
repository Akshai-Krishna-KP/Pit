// ██████╗  ██╗ ████████╗
// ██╔══██╗ ██║ ╚══██╔══╝
// ██████╔╝ ██║    ██║   
// ██╔═══╝  ██║    ██║   
// ██║      ██║    ██║   
// ╚═╝      ╚═╝    ╚═╝   

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtin.h"
#include "pitcmdset.h"

#define CMD_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// Connect to other function and file using a function pointer
struct pit_cmd {
    const char* cmd_name;
    int (*fn)(int, const char**);
    unsigned int option;
};

// Array of the possible pit command 
// Add in lexicographic ordering to use Binary search in find-command().
static struct pit_cmd cmd[] = {
    {"add", cmd_add, 0},
    {"hash-object", cmd_hash_object, 0},
    {"help", cmd_help, 0},
    {"start", cmd_start, 0},
};

// Find the position of the struct in the cmd array and return it.
struct pit_cmd* find_command(const char *argv) {
    for(int i=0; i<CMD_SIZE(cmd); i++) {
        struct pit_cmd *p = cmd + i;
        if(!strcmp(argv, p->cmd_name))
            return p;
    }
    return NULL;
}

int error_checkup(int error_code) {
    switch (error_code) {
    case 1:
        break;
    default:
        printf("Finished Succesfully\n");
        break;
    }
}


int main(int argc,const char **argv) {
    argc--;
    argv++;

    const char *cmd;
    if(!argc) {
        cmd = "help";
        return 0;
    }

    struct pit_cmd *cmd_struct = find_command(argv);

    int error = error_checkup(cmd_struct->fn(argc - 1, argv + 1));
    
    return 0;
}

