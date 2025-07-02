//  ███████╗ ████████╗  █████╗  ██████╗  ████████╗
//  ██╔════╝ ╚══██╔══╝ ██╔══██╗ ██╔══██╗ ╚══██╔══╝
//  ███████╗    ██║    ███████║ ██████╔╝    ██║   
//  ╚════██║    ██║    ██╔══██║ ██╔══██╗    ██║   
//  ███████║    ██║    ██║  ██║ ██║  ██║    ██║   
//  ╚══════╝    ╚═╝    ╚═╝  ╚═╝ ╚═╝  ╚═╝    ╚═╝   

// This file is a simple replica of the Git Init command.
// This will create essential Directory(Folder) and FIle that act as the backbone of the version control

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int make_dir(const char* path) {
    if(mkdir(path, 0755) == 0) {
        return 0;
    }
    else {
        if(errno == EEXIST) {
            printf("Directory already exist.\n");
        }
        else {
            perror("mkdir");
        }

        return -1;
    }
}

int main() {
    // Main pit file
    const char* pit_dir = ".pit";

    // Create .pit folder
    make_dir(pit_dir);

    // Make other directory/folder

    char path[256];

    const char *subdir[] = {
        "branches", "objects", "refs", "objects/info", "objects/pack", "refs/heads", "refs/tags", "refs/remotes"
    };

    for(int i = 0; i < sizeof(subdir)/sizeof(subdir[0]); i++) {
        snprintf(path, sizeof(path), "%s/%s", pit_dir, subdir[i]);
        if(make_dir(path) != 0) {
            return -1;
        }
    }

    // Make config file
    snprintf(path, sizeof(path), "%s/config", pit_dir);
    FILE *config = fopen(path, "w");
    if(config == NULL) {
        perror("fopen config");
        return -2;
    }
    fprintf(config, "[core]\n"
                    "\trepositoryformatversion = 0\n"
                    "\tfilemode = true\n"
                    "\tbare = false\n"
                    "\tlogallrefupdates = true\n");
    fclose(config);

    //Make HEAD file
    snprintf(path, sizeof(path), "%s/HEAD", pit_dir);
    FILE *HEAD = fopen(path, "w");
    if(HEAD == NULL) {
        perror("fopen HEAD");
        return -2;
    }
    fprintf(HEAD, "ref: refs/heads/master\n");
    fclose(HEAD);

    //Make description file
    snprintf(path, sizeof(path), "%s/description", pit_dir);
    FILE *description = fopen(path, "w");
    if(description == NULL) {
        perror("fopen description");
        return -2;
    }
    fprintf(description, "Unnamed Repo: add name and details about your repo\n");
    fclose(description);

    // inform the Completion
    printf("Started Pit repository in .pit\nHandle with care, it might break\nreport issue in the Github repo");

}