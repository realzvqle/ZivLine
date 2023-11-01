#include "header/zivline.h"


bool moveDirectory(ziv *pointer){

    if(!pointer->args){
        printf("moveto: moveto *directory, Moves To that directory\n");
        return FALSE;
    }


    if(!SetCurrentDirectory(pointer->args)){
        DWORD error = GetLastError();
        fprintf(stderr, "Failed Changing Directory, Error %d\n", error);
        return FALSE;
    }

    pointer->path = (char*)malloc(strlen(pointer->args) + 1);
    strcpy(pointer->path, pointer->args);

    printf("Sucsessfully Changed Directory To %s\n", pointer->path);
    return TRUE;
}

bool listFiles(ziv *pointer){
    char* path = NULL;
    char* temp = NULL;
    int stat = 0;
    if(!pointer->path && !pointer->args){
        TCHAR buffer[BUFSIZE];
        DWORD length = GetCurrentDirectory(BUFSIZE, buffer);
        path = (char*)malloc(strlen(buffer) + 1);
        strcpy(path, buffer);
        goto START;
    }
    //char* path = "";

    if(!pointer->args && pointer->path){
        stat = 1;
        temp = (char*)malloc(strlen(pointer->path) + 3);
        strcpy(temp, pointer->path);
        path = (char*)malloc(strlen(pointer->path) + 3);
        strcpy(path, pointer->path);
        strcat(path, "\\");
        goto START;
    }
     
    int i = 0;
    if(!pointer->path && pointer->args){
        path = (char*)malloc(strlen(pointer->args) + 3);
        strcpy(path, pointer->args);
        strcat(path, "\\");
        stat = 1;
        goto START;
    }
    else {
        path = (char*)malloc(strlen(pointer->path) + 3);
        strcpy(path, pointer->path);
        strcat(path, "\\");
    }
START:
    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(strcat(path, "\\*"),  &fd);
    if(hFind == INVALID_HANDLE_VALUE){
        printf("Error Opening Directory, Error Code %d\n", GetLastError());
        free(path); 
        free(temp); 
        return FALSE;
    }
    do {
        printf("%s  ", fd.cFileName);
        i++;
        if(i % 5 == 0) printf("\n");
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
             printf("[%s] ", fd.cFileName);
        }
    } while (FindNextFile(hFind, &fd) != 0);
    printf("\n");
    FindClose(hFind);
    if(stat == 1){
        return TRUE;
    }
    if(!pointer->path && !pointer->args){
        return TRUE;
    }
    pointer->path = (char*)malloc(strlen(temp) + 1);
    strcpy(pointer->path, temp);
    free(temp);
    return TRUE;
}
