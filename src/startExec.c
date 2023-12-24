#include "header/zivline.h"


void StartProcess(ziv *pointer){
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(STARTUPINFO);

    if(!CreateProcessA(pointer->args,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
        printf("Failed Creating Process, Error: %d\n", GetLastError());
        return;
    }    
}

void startwithadmin(char* cmd, char* param, ziv *pointer) {
    //char* cmd = strtok(pointer->cmds, "./");
    HINSTANCE hResult = ShellExecuteA(NULL, "runas", cmd, param, NULL, SW_SHOW);
    
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

        HINSTANCE hResult2 = ShellExecuteA(NULL, "runas", path, param, NULL, SW_SHOW);
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

void startwithoutadmin(char* cmd, char* param, ziv *pointer) {
    //char* cmd = strtok(pointer->cmds, "./");
    HINSTANCE hResult = ShellExecuteA(NULL, "open", cmd, param, NULL, SW_SHOW);
    
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

void Start(ziv *pointer){
    char * args = strtok(pointer->args, " \n");
    char * first = strtok(NULL, " \n");
    char * second = strtok(NULL, "\n");

    if(!args || !first){
        printf("Syntax: start *perm *executable *parameters\nif perm = \"admin\", it runs as admin\nelse if perm = \"user\", it runs with normal user permissions\n");
        return;
    }

    if(strcmp(args, "admin") == 0){
        
        startwithadmin(first, second, pointer);
    }
    else if(strcmp(args, "user") == 0){
        
        startwithoutadmin(first, second, pointer);

    }
    else{
        printf("Syntax: start *perm *executable *parameters\nif perm = \"admin\", it runs as admin\nelse if perm = \"user\", it runs with normal user permissions\n");
        return;
    }
     
}

