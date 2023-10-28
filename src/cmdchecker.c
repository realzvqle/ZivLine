#include "header/zivline.h"



char *cmdArray[] = {"echo", "help", "\\", "ver", "start", "execute", "clr", "pause", "read", "write", "create", "exit", "zwrite", "run", "system", "moveto", "cd", "pd"};




bool cmdChecker(ziv *pointer){
    bool foundCommand = false;
    int cmdSize = sizeof(cmdArray)/sizeof(cmdArray[0]);
    if(!pointer->cmds) return false;
    toLowerCase(pointer->cmds);
    for(int i = 0; i < cmdSize; i++){
        if(strcmp(pointer->cmds, cmdArray[i]) == 0){
            cmdExecute(i, pointer);
            return true;
        }
    }
    printf("%s is the wrong command, please type \"help\" to see a list of cmds\n", pointer->cmds);
    return false;
}



void cleanup(ziv *pointer){
    if(!pointer->path) return;
    else free(pointer->path);

    return;
}


