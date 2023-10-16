#include "header/zivline.h"



char *cmdArray[] = {"echo", "welcome", "\\"};

bool cmdChecker(ziv *pointer){
    bool foundCommand = false;
    int cmdSize = sizeof(cmdArray)/sizeof(cmdArray[0]);
    if(!pointer->cmds) return false;
    char *lowerCmd = toLowerCase(pointer->cmds);
    for(int i = 0; i < cmdSize; i++){
        if(strcmp(lowerCmd, cmdArray[i]) == 0){
            cmdExecute(i, pointer);
            return true;
        }
    }
    printf("%s is the wrong command, please type \"help\" to see a list of cmds\n", pointer->cmds);
    return false;
}

