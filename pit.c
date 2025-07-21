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

// Connect to other function and file using a function pointer
struct pit_cmd {
    const char* cmd_name;
    int (*fn)(int, const char**, const char*, struct repository);
    unsigned int option;
};

static struct pit_cmd cmd[] = {
    {"start", cmd_start, 0},
    {"hash-object", cmd_hash_object, 0},
};

int main() {
    
}

