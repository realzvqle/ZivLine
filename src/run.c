#include "header/zivline.h"


void startExecute(ziv* pointer) {
    char* cmd = strtok(pointer->cmds, ",,");
    if(!cmd){
        printf("??\n");
        return;
    }
    if (cmd) {
        printf("Checking Local Directory For %s...\n", cmd);
        
        char path[BUFSIZE] = "";
        
        if (strcmp(pointer->path, "EMPTYSTRING") == 0) {
            strcpy(path, cmd);
        } else {
            Sleep(500);
            strcpy(path, pointer->path);
            strcat(path, "\\");
            strcat(path, cmd);
        }
        if (strlen(path) >= 4 && path[strlen(path) - 4] == '.' && path[strlen(path) - 3] == 'z' && path[strlen(path) - 2] == 'l' && path[strlen(path) - 1] == 's') {
            pointer->args = (char*)malloc(strlen(cmd) + 1);
            if (pointer->args != NULL) {
                strcpy(pointer->args, cmd);
                startFileReaderOnShell(pointer);
            } else {
                
                printf("Memory allocation failed\n");
            }
            free(pointer->args);
            return;
       }
        BOOL result2 = StartProcessA(path, pointer->args);
        if (!result2) {
            if (strlen(cmd) >= 4 && cmd[strlen(cmd) - 4] == '.' && cmd[strlen(cmd) - 3] == 'z' && cmd[strlen(cmd) - 2] == 'l' && cmd[strlen(cmd) - 1] == 's') {
            //printf("hm\n");
                pointer->args = (char*)malloc(strlen(cmd) + 1);
                if (pointer->args != NULL) {
                    strcpy(pointer->args, cmd);
                    startFileReaderOnShell(pointer);
                } else {
                    printf("Memory allocation failed\n");
                }
                free(pointer->args);

                return;
            }
            else{
                BOOL result = StartProcessA(cmd, pointer->args);
                if(!result){
                        printf("Program Does Not Exist\n");
                }
            }
            return;
        }
        else {
            printf("Ran %s Successfully\n", cmd);
            return;
        }
    }
    else{
        printf("Ran %s Successfully\n", cmd);
        return;
    }
}

