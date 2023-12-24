#include "header\zivline.h"

void copyFile(ziv *pointer) {
    if (!pointer->args) {
        printf("copy *firstfile *secondfile\n");
        return;
    }

    char *firstFile = strtok(pointer->args, " \n");
    char *secondFile = strtok(NULL, "\n");
    printf("First Path is %s, Second Path is %s\n", firstFile, secondFile);

    if (!secondFile) {
        printf("copy *firstfile *secondfile\n");
        return;
    }

    char path[BUFSIZE] = "";
    if (strcmp(pointer->path, "EMPTYSTRING") == 0) {
        snprintf(path, sizeof(path), "%s", firstFile);
    } else {
        snprintf(path, sizeof(path), "%s\\%s", pointer->path, firstFile);
    }

    char secondPath[BUFSIZE] = "";
    if (strcmp(pointer->path, "EMPTYSTRING") == 0) {
        snprintf(secondPath, sizeof(secondPath), "%s", secondFile);
    } else {
        snprintf(secondPath, sizeof(secondPath), "%s\\%s", pointer->path, secondFile);
    }

    FILE *sourceFile, *destinationFile;
    char buffer[4096];
    size_t bytesRead;

    printf("First Path is %s, Second Path is %s\n", path, secondPath);

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
        if (fwrite(buffer, 1, bytesRead, destinationFile) != bytesRead) {
            perror("Error writing to destination file");
            break;
        }
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