// ██╗  ██╗ █████╗ ███████╗██╗  ██╗       ██████╗ ██████╗      ██╗███████╗ ██████╗████████╗
// ██║  ██║██╔══██╗██╔════╝██║  ██║      ██╔═══██╗██╔══██╗     ██║██╔════╝██╔════╝╚══██╔══╝
// ███████║███████║███████╗███████║█████╗██║   ██║██████╔╝     ██║█████╗  ██║        ██║   
// ██╔══██║██╔══██║╚════██║██╔══██║╚════╝██║   ██║██╔══██╗██   ██║██╔══╝  ██║        ██║   
// ██║  ██║██║  ██║███████║██║  ██║      ╚██████╔╝██████╔╝╚█████╔╝███████╗╚██████╗   ██║   
// ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝       ╚═════╝ ╚═════╝  ╚════╝ ╚══════╝ ╚═════╝   ╚═╝   
// 
// This is a replica of Git hash-objects. user can use this to see the hash value of object or
// to wirte the hashed object into .git/objects folder.
// This will only work for Blob right now, will add other object type if deemed neccessary


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <openssl/sha.h>

// Show the error message 
void fatal_error(const char* msg, const char* objectName) {
    if(objectName) {
        fprintf(stderr, "[Error]: %s: %s\n", msg, objectName);
    }
    else {
        fprintf(stderr, "[Error]: %s\n", msg);
    }
    
    exit(1);
}

// Check if the file exist 
int file_exists(const char *objectName) {
    struct stat st;
    return stat(objectName, &st) == 0;
}

// Convert Integer to String dynamically
char* int_to_str(int num) {
    int len = snprintf(NULL, 0, "%d", num);
    char* str = malloc(len + 1);
    if(str) {
        sprintf(str, "%d", num);
    }
    return str;
}

int main(int argc, char *argv[]) {
                                            
    int write_flag = 0;
    const char* type = "blob";
    const char* objectName = NULL;

    if(argc < 2) {
        fprintf(stderr, "usage: pit hash-object [-w] [-t <type>] <file>\n");
        return 1;
    }



    // Take all the other argument and do some shit
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-w") == 0) {
            write_flag = 1;
        }
        else if(strcmp(argv[i], "-t") == 0) {
            // check if file type is given
            if(i + 1 >= argc) {
                fatal_error("[-t] need a Object type specified,Read the fu**ng manual", NULL);
            }

            // Check the file type is valid
            const char* object_type = argv[++i];
            if(strcmp(object_type, "blob") != 0 && strcmp(object_type, "tree") != 0 && strcmp(object_type, "commit") != 0 && strcmp(object_type, "tag") != 0){
                fatal_error("Hello Einstein, i was not aware you were trying to invent a new object type.\n Not Valid", object_type);
            }

            // Assign object_type type
            type = object_type;
        }
        else {
            if(objectName != NULL) {
                fatal_error("Multiple Object included, try one at a time motherfu***er", NULL);
            }
            objectName = argv[i];
        }
    }

    if(objectName == NULL) {
        fatal_error("No objectName included", NULL);
    }
    if(!file_exists(objectName)) {
        fatal_error("Can't open the Object.Check whether the object exist", objectName);
    }

    /////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    // |                   _)              _ )         |   |               |     _)              
    // |       _ \    _` |  |   __|        _ \ \       |   |   _` |   __|  __ \   |  __ \    _` |
    // |      (   |  (   |  |  (          ( `  <       ___ |  (   | \__ \  | | |  |  |   |  (   |
    // _____| \___/  \__, | _| \___|      \___/\/      _|  _| \__,_| ____/ _| |_| _| _|  _| \__, |
    //             |___/                                                                  |___/ 

    if(strcmp(type, "blob") != 0) {
        printf("Currently it can only hash Blob.\n");
        return 2;
    }

    FILE* filename = fopen(objectName, "rb");
    if(!filename) {
        perror("fopen");
        return 1;
    }

    // get file size
    struct stat st;
    if(stat(objectName, &st) != 0) {
        perror("stat");
        fclose(filename);
        return 1;
    }
    size_t filesize = st.st_size;

    // Allocate buffer for file content + header
    char header[64];
    int header_len = snprintf(header, sizeof(header), "blob %zu%c", filesize, '\0');
    size_t total_len = header_len + filesize;
    unsigned char *buffer = malloc(total_len);
    if(!buffer) {
        fclose(filename);
        fatal_error("Memory Allocaion Failed", objectName);
    }

    // Copy header and file content into buffer
    memcpy(buffer, header, header_len);
    if(fread(buffer + header_len, 1, filesize, filename) != filesize) {
        free(buffer);
        fclose(filename);
        fatal_error("Failed to read file", objectName);
    }

    fclose(filename);

    // Compute SHA-1
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(buffer, total_len, hash);

    // Print Hash
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    free(buffer);

    return 0;
}