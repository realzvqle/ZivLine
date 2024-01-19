#include "header/zivline.h"


extern ziv pointer;

BOOL startShell(cli *clipointer){


    ziv secondPointer;
    secondPointer.state = 3;
    secondPointer.path = (char*)malloc(BUFSIZE);
    strcpy(secondPointer.path, "EMPTYSTRING");
    secondPointer.exit = FALSE;
    BOOL loop = TRUE;
    printf("\n");
    while(loop == TRUE && !secondPointer.exit){
        if(secondPointer.exit) break;
        printf("-> ");
        fgets(clipointer->buffer, BUFSIZE, stdin);
        strtok(clipointer->buffer, "\n");
        secondPointer.cmds, secondPointer.args = cmdParser(clipointer->buffer, &secondPointer);
        pointer = secondPointer;

        cmdChecker(&secondPointer);
    }
    return TRUE;
}