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

void Start(ziv *pointer){
    char * args = strtok(pointer->args, " \n");
    char * first = strtok(NULL, " \n");
    char * second = strtok(NULL, "\n");

    if(!args || !first){
        printf("Syntax: start *perm *executable *parameters\nif perm = \"admin\", it runs as admin\nelse if perm = \"user\", it runs with normal user permissions\n");
        return;
    }

    if(strcmp(args, "admin") == 0){
        if(!ShellExecuteA(NULL, "runas", first, second, NULL, SW_SHOW)){
            printf("Failed Creating Process, Error: %d\n", GetLastError());
            return;
        } 
    }
    else if(strcmp(args, "user") == 0){
        if(!ShellExecuteA(NULL, "open", first, second, NULL, SW_SHOW)){
            printf("Failed Creating Process, Error: %d\n", GetLastError());
            return;
        } 
    }
    else{
        printf("Syntax: start *perm *executable *parameters\nif perm = \"admin\", it runs as admin\nelse if perm = \"user\", it runs with normal user permissions\n");
        return;
    }
     
}

