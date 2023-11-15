#include "header/zivline.h"





bool isDirectoryValid(char* path){
    DWORD check = GetFileAttributesA(path);

    if(check == INVALID_FILE_ATTRIBUTES) return FALSE;
    else return TRUE;
}

void printDir(ziv *pointer){

    if(!pointer->path) goto CURDIR;
    printf("Current Directory Is %s\n", pointer->path);


    return;
CURDIR:
    TCHAR buffer[BUFSIZE];
    DWORD length = GetCurrentDirectory(BUFSIZE, buffer);
    char* path = (char*)malloc(strlen(buffer) + 1);
    strcpy(path, buffer);
    printf("Current Directory Is %s\n", path);
    free(path);
    return;

}

char* getDir(){
    char* path = NULL;
    TCHAR buffer[BUFSIZE];
    DWORD length = GetCurrentDirectory(BUFSIZE, buffer);
    path = (char*)malloc(strlen(buffer) + 1);
    strcpy(path, buffer);
     if (path[strlen(path) - 1] != '\\') {
        // If not, add a backslash at the end
        strcat(path, "\\");
    }

    return path;

}

char* currentDir(ziv *pointer){
    return pointer->path;
}



bool moveDirectory(ziv *pointer){
    if(!pointer->args){
        printf("moveto: moveto *directory\\, Moves To that directory\n");
        return FALSE;
    }
    char* tempPath = NULL;

    if(pointer->args[strlen(pointer->args) - 1] != '\\'){
        printf("missing \\ in the end\n");
        return FALSE;
    }
    toLowerCase(pointer->args);
    // if(!SetCurrentDirectory(pointer->args)){
    //     DWORD error = GetLastError();
    //     fprintf(stderr, "Failed Changing Directory, Error %d\n", error);
    //     return FALSE;
    // }
    
    if(pointer->args[1] == ':'){
        goto CHANGEPATH;
    }
    else{
        goto ADDPATH;
    }

    return TRUE;
CHANGEPATH:
    tempPath = (char*)malloc(strlen(pointer->args) + 1);
    strcpy(tempPath, pointer->args);

    if(!isDirectoryValid(tempPath)){
        printf("Directory Does Not Exist\n");
        free(tempPath);
        return FALSE;
    }
    
    if(!pointer->path);
    else free(pointer->path);
    pointer->path = NULL;
    pointer->path = (char*)malloc(strlen(tempPath) + 1);
    strcpy(pointer->path, tempPath);
    free(tempPath);
    printf("Sucsessfully Changed Directory To %s\n", pointer->path);
    
    return TRUE;
ADDPATH:
    if(!pointer->path){
        tempPath = (char*)malloc(strlen(getDir()) + 1);
        strcpy(tempPath, getDir());
    }
    else{
        tempPath = (char*)malloc(strlen(pointer->path) + 1);
        strcpy(tempPath, pointer->path);
    }
    int totalLength = strlen(tempPath) + strlen(pointer->args) + 1;
    char* result = (char*)malloc(totalLength);
    strcpy(result, tempPath);
    strcat(result, pointer->args);
    tempPath = (char*)malloc(strlen(result) + 1);
    strcpy(tempPath, result);
    free(result);
    if(!isDirectoryValid(tempPath)){
        printf("Directory Does Not Exist\n");
        free(tempPath);
        return FALSE;
    }
    if(!pointer->path);
    else free(pointer->path);
    pointer->path = NULL;
    pointer->path = (char*)malloc(strlen(tempPath) + 1);
    strcpy(pointer->path, tempPath);
    free(tempPath);
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
        if(GetLastError() == 3){
            printf("The Directory Does Not Exist\n");
            free(path); 
            free(temp); 
            return FALSE;
        }
        else if(GetLastError() == 5){
            printf("Permission Is Denied\n");
            free(path); 
            free(temp); 
            return FALSE;
        }
        printf("Error Opening Directory, Error Code %d\n", GetLastError());
        free(path); 
        free(temp); 
        return FALSE;
    }
    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
             printf("[%s] ", fd.cFileName);
        }
        else printf("%s  ", fd.cFileName);
        i++;
        if(i % 5 == 0) printf("\n");
    } while (FindNextFile(hFind, &fd) != 0);
    printf("\n");
    FindClose(hFind);
    if(stat == 1){
        return TRUE;
    }
    if(!pointer->path && !pointer->args){
        return TRUE;
    }
    if(pointer->args){
        return TRUE;
    }
    pointer->path = (char*)malloc(strlen(temp) + 1);
    strcpy(pointer->path, temp);
    free(temp);
    return TRUE;
}
