#include "header/zivline.h"

extern ziv pointer;


BOOL startFileReader(freader *fpointer){
    ziv secondPointer;
    secondPointer.state = 1;
    secondPointer.path = (char*)malloc(BUFSIZE);
    strcpy(secondPointer.path, "EMPTYSTRING");
    fpointer->fp = fopen(fpointer->fileName, "r");
    if(!fpointer->fp){
        printf("Failed Opening File\n");
        return FALSE;
    }
    secondPointer.exit = FALSE;
    while(fgets(fpointer->buffer, BUFSIZE, fpointer->fp)){
        pointer = secondPointer;
        if(secondPointer.exit) break;
        strtok(fpointer->buffer, "\n");
        secondPointer.cmds, secondPointer.args = cmdParser(fpointer->buffer, &secondPointer);
        pointer = secondPointer;
        cmdChecker(&secondPointer);
    }
    if(!secondPointer.exit) cleanup(&secondPointer);
    fclose(fpointer->fp);
}