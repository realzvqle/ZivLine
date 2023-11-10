#include "header/zivline.h"




void newMakeDirectory(ziv *pointer){
    if(!pointer->args){
        printf("makedir *dir - makes the directory\n");
        return;
    }
    char* temp = NULL;
    char* cPath = NULL;
    if(!pointer->path) cPath = pointer->args;
    else{
       temp = (char*)malloc(strlen(pointer->path) + 1);
       strcpy(temp, pointer->path); 
       cPath = pointer->path;
       strcat(cPath, "\\");
       strcat(cPath, pointer->args);
    } 
    
    int status = _mkdir(cPath);
    if(status != 0){
        printf("Failed Making Directory: ");
        perror("_mkdir");
        if(pointer->path) goto FREE;
        return;
    }
    else{
         printf("Sucsessfully Made %s\n", cPath);
         if(pointer->path) goto FREE;
    }
    return;
FREE:
    free(pointer->path);
    pointer->path = (char*)malloc(strlen(temp) + 1);
    strcpy(pointer->path, temp);
    free(temp);
    return;
}

void newDeleteDirectory(ziv *pointer){
    if(!pointer->args){
        printf("deldir *dir - deletes the directory\n");
        return;
    }
    char* temp = NULL;
    char* cPath = NULL;
    if(!pointer->path) cPath = pointer->args;
    else{
        temp = (char*)malloc(strlen(pointer->path) + 1);
        strcpy(temp, pointer->path);
        cPath = pointer->path;
        strcat(cPath, "\\");
        strcat(cPath, pointer->args);
    } 
    
    int status = _rmdir(cPath);
    if(status != 0){
        printf("Failed Removing Directory: ");
        perror("_rmdir");
        if(pointer->path) goto FREE;
        return;
    }
    else{
        if(pointer->path) goto FREE;
        printf("Sucsessfully Removed %s\n", cPath);
    }
    return;
FREE:
    free(pointer->path);
    pointer->path = (char*)malloc(strlen(temp) + 1);
    strcpy(pointer->path, temp);
    free(temp);
    return;
}