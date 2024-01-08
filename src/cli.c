#include "header/zivline.h"

ziv pointer;

BOOL startCLI(cli *clipointer){
    
    
    pointer.path = (char*)malloc(BUFSIZE);
    strcpy(pointer.path, "EMPTYSTRING");
    pointer.exit = FALSE;
    BOOL loop = TRUE;
    printf("\n");
    while(loop == TRUE && !pointer.exit){
        if(pointer.exit) break;
        printf("-> ");
        fgets(clipointer->buffer, BUFSIZE, stdin);
        strtok(clipointer->buffer, "\n");
        pointer.cmds, pointer.args = cmdParser(clipointer->buffer, &pointer);
        cmdChecker(&pointer);
    }
    cleanup(&pointer);
    return TRUE;
}