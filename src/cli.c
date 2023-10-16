#include "header/zivline.h"

bool startCLI(cli *clipointer){
    ziv pointer;
    bool loop = true;
    printf("ZivLine [Version %0.1f]\n(c) zvqle, All rights reserved\n\n", VER);
    while(loop == true){
        printf("> ");
        fgets(clipointer->buffer, BUFSIZE, stdin);
        strtok(clipointer->buffer, "\n");
        pointer.cmds, pointer.args = cmdParser(clipointer->buffer, &pointer);
        cmdChecker(&pointer);
    }
    return true;
}