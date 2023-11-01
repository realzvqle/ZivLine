#include "header/zivline.h"




void newMakeDirectory(ziv *pointer){
    char* cPath = NULL;
    if(!pointer->path) cPath = pointer->args;
    else{
       cPath = pointer->path;
       strcat(cPath, "\\");
       strcat(cPath, pointer->args);
    } 
    
    int status = _mkdir(cPath);
    if(status != 0){
        printf("Failed Making Directory: ");
        perror("_mkdir");
        return;
    }
    else printf("Sucsessfully Made %s\n", cPath);
    return;
}

void newDeleteDirectory(ziv *pointer){
    char* cPath = NULL;
    if(!pointer->path) cPath = pointer->args;
    else{
       cPath = pointer->path;
       strcat(cPath, "\\");
       strcat(cPath, pointer->args);
    } 
    
    int status = _rmdir(cPath);
    if(status != 0){
        printf("Failed Removing Directory: ");
        perror("_rmdir");
        return;
    }
    else printf("Sucsessfully Removed %s\n", cPath);
    return;
}