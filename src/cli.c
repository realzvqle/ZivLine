#include "header/zivline.h"

extern ziv pointer;

BOOL startCLI(cli *clipointer){
    
    pointer.state = 0;
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
        cmdParser(clipointer->buffer, &pointer);
        cmdChecker(&pointer);
    }
    cleanup(&pointer);
    return TRUE;
}