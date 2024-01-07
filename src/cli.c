#include "header/zivline.h"

ziv pointer;

bool startCLI(cli *clipointer){
    
    
    pointer.path = (char*)malloc(BUFSIZE);
    strcpy(pointer.path, "EMPTYSTRING");
    pointer.exit = false;
    bool loop = true;
    printf("\n");
    while(loop == true && !pointer.exit){
        if(pointer.exit) break;
        printf("-> ");
        fgets(clipointer->buffer, BUFSIZE, stdin);
        strtok(clipointer->buffer, "\n");
        pointer.cmds, pointer.args = cmdParser(clipointer->buffer, &pointer);
        cmdChecker(&pointer);
    }
    cleanup(&pointer);
    return true;
}