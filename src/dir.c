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
    char* path = "";
    int i = 0;
    if(!pointer->path && !pointer->args){
        printf("No Path Change, And No Arguments, Please Put A Directory Argument or Change The Path\n");
        return FALSE;
    }
    if(!pointer->path && pointer->args){
        path = pointer->args;
    }
    else{
        path = pointer->path;
    }
    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(strcat(path, "\\*"),  &fd);
    if(hFind == INVALID_HANDLE_VALUE){
        perror("hFind");
        return FALSE;
    }
    do {
        printf("%s  ", fd.cFileName);
        i++;
        if(i % 5 == 0) printf("\n");
    } while (FindNextFile(hFind, &fd) != 0);
    printf("\n");
    FindClose(hFind);
    return TRUE;
}