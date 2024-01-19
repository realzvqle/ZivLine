#include "header/zivline.h"

extern ziv pointer;


BOOL startFileReaderOnShell(ziv *pointerPass){
    if(!pointerPass->args){
        printf("read: read *filename, opens a handle to filename and reads it\n");
        return FALSE;
    }
    FILE *fp;
    char path[BUFSIZE] = "";
    if(strcmp(pointerPass->path, "EMPTYSTRING") == 0) strcpy(path, pointerPass->args);
    else{
        Sleep(500);
        strcpy(path, pointerPass->path);
        strcat(path, "\\");
        strcat(path, pointerPass->args);
    }
    char buffer[BUFSIZE];
    ziv secondPointer;
    secondPointer.state = 4;
    secondPointer.path = (char*)malloc(sizeof(pointerPass->path) + 1);
    strcpy(secondPointer.path, pointerPass->path);
    fp = fopen(path, "r");
    if(!fp){
        printf("Failed Opening File\n");
        return FALSE;
    }
    secondPointer.exit = FALSE;
    while(fgets(buffer, BUFSIZE, fp)){
        if(secondPointer.exit) break;
        strtok(buffer, "\n");
        secondPointer.cmds, secondPointer.args = cmdParser(buffer, &secondPointer);
        pointer = secondPointer;
        cmdChecker(&secondPointer);

    }
    secondPointer.path = (char*)malloc(128);
    cleanup(&secondPointer);
    fclose(fp);
}