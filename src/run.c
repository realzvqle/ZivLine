#include "header/zivline.h"


void startExecute(ziv* pointer) {
    char* cmd = strtok(pointer->cmds, "./");
    HINSTANCE hResult = ShellExecuteA(NULL, "open", cmd, pointer->args, NULL, SW_SHOW);
    
    if ((intptr_t)hResult <= 32 || (intptr_t)hResult == HINSTANCE_ERROR) {
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

        HINSTANCE hResult2 = ShellExecuteA(NULL, "open", path, pointer->args, NULL, SW_SHOW);
        if ((intptr_t)hResult2 <= 32 || (intptr_t)hResult2 == HINSTANCE_ERROR) {
            printf("Couldn't Run %s\n", cmd);
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

