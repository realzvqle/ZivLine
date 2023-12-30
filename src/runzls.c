#include "header/zivline.h"




bool startFileReaderOnShell(ziv *pointer){
    if(!pointer->args){
        printf("read: read *filename, opens a handle to filename and reads it\n");
        return FALSE;
    }
    FILE *fp;
    char path[BUFSIZE] = "";
    if(strcmp(pointer->path, "EMPTYSTRING") == 0) strcpy(path, pointer->args);
    else{
        Sleep(500);
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, pointer->args);
    }
    char buffer[BUFSIZE];
    ziv secondPointer;
    secondPointer.path = (char*)malloc(sizeof(pointer->path) + 1);
    strcpy(secondPointer.path, pointer->path);
    fp = fopen(path, "r");
    if(!fp){
        printf("Failed Opening File\n");
        return false;
    }
    secondPointer.exit = false;
    while(fgets(buffer, BUFSIZE, fp)){
        if(secondPointer.exit) break;
        strtok(buffer, "\n");
        secondPointer.cmds, secondPointer.args = cmdParser(buffer, &secondPointer);
        cmdChecker(&secondPointer);
    }
    secondPointer.path = (char*)malloc(128);
    cleanup(&secondPointer);
    fclose(fp);
}