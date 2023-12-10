#include "header\zivline.h"



void copyFile(ziv *pointer){

    if(!pointer->args){
        printf("copy *firstfile *secondfile\n");
        return;
    }


    char* firstFile;
    char* secondFile;

    firstFile = strtok(pointer->args, " \n");
    secondFile = strtok(NULL, "\n");


    if(!secondFile){
        printf("copy *firstfile *secondfile\n");
        return;
    }

    char path[BUFSIZE] = "";
    if(strcmp(pointer->path, "EMPTYSTRING") == 0) strcpy(path, firstFile);
    else{
        Sleep(500);
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, firstFile);
    }

    char secondPath[BUFSIZE] = "";
    if(strcmp(pointer->path, "EMPTYSTRING") == 0) strcpy(path, secondFile);
    else{
        Sleep(500);
        strcpy(secondPath, pointer->path);
        strcat(secondPath, "\\");
        strcat(secondPath, secondFile);
    }

    FILE* sourceFile, * destinationFile;
    char buffer[4096];
    size_t bytesRead;

    sourceFile = fopen(path, "rb");

    if (sourceFile == NULL) {
        perror("Error opening source file");
        return;
    }

    
    destinationFile = fopen(secondPath, "wb");

    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return;
    }

    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    
    fclose(sourceFile);
    fclose(destinationFile);
}


BOOL removeFile(ziv *pointer){
    if(!pointer->args){
        printf("delete *filename\n");
        return FALSE;
    }

    char path[BUFSIZE] = "";
    if(strcmp(pointer->path, "EMPTYSTRING") == 0) strcpy(path, pointer->args);
    else{
        Sleep(500);
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, pointer->args);
    }

    if (remove(path) == 0) {
        printf("File %s deleted successfully.\n", pointer->args);
    } else {
        perror("Error deleting file");
    }

    return TRUE;
}