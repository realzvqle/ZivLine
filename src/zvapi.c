#include "header/zivline.h"


#define zvapiPrintf(message, ...) printf("ZVAPI - " message, ##__VA_ARGS__)


static void zvapiFunctionChecker(char* cmd, ziv* pointer){
    cmd = toLowerCase(cmd);
    if(strcmp(cmd, "startdebugmode") == 0){
        zvapiPrintf("Started Debug Mode\n");
        pointer->state = 9;
    }
    if(strcmp(cmd, "printstate") == 0){
        zvapiPrintf("%d\n", pointer->state);
        pointer->state = 9;
    }
}


void zvapiFunctionParser(ziv* pointer){
    char* cmd = strtok(pointer->cmds, "-");
    char* args = strtok(NULL, " ");
    if(!args){
        return;
    }
    zvapiFunctionChecker(args, pointer);    
}