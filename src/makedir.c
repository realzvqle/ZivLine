#include "header/zivline.h"




void newMakeDirectory(ziv* pointer) {
    if (!pointer->args) {
        printf("makedir *dir - makes the directory\n");
        return;
    }

    if (pointer->args[strlen(pointer->args) - 1] == '\\') {
        printf("Invalid Name!\n");
        return;
    }

    char* temp = NULL;
    char* cPath = NULL;

    if (!pointer->path) {
        cPath = (char*)malloc(strlen(pointer->args) + 1);
        strcpy(cPath, pointer->args);
    } else {
        temp = (char*)malloc(strlen(pointer->path) + 1);
        strcpy(temp, pointer->path);
        cPath = (char*)malloc(strlen(pointer->path) + strlen(pointer->args) + 2);
        strcpy(cPath, pointer->path);
        strcat(cPath, "\\");
        strcat(cPath, pointer->args);
    }

    int status = _mkdir(cPath);

    if (status != 0) {
        perror("Failed Making Directory: ");
    } else {
        printf("Successfully Made %s\n", cPath);
    }

    free(cPath);
    free(temp);
}

void newDeleteDirectory(ziv* pointer) {
    if (!pointer->args) {
        printf("deldir *dir - delets the directory\n");
        return;
    }

    if (pointer->args[strlen(pointer->args) - 1] == '\\') {
        printf("Invalid Name!\n");
        return;
    }

    char* temp = NULL;
    char* cPath = NULL;

    if (!pointer->path) {
        cPath = (char*)malloc(strlen(pointer->args) + 1);
        strcpy(cPath, pointer->args);
    } else {
        temp = (char*)malloc(strlen(pointer->path) + 1);
        strcpy(temp, pointer->path);
        cPath = (char*)malloc(strlen(pointer->path) + strlen(pointer->args) + 2);
        strcpy(cPath, pointer->path);
        strcat(cPath, "\\");
        strcat(cPath, pointer->args);
    }

    int status = _rmdir(cPath);

    if (status != 0) {
        perror("Failed Deleting Directory: ");
    } else {
        printf("Successfully Deleted %s\n", cPath);
    }

    free(cPath);
    free(temp);
}