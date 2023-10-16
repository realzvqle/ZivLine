#include "header/zivline.h"


char* cmdParser(char buffer[], ziv *pointer){
    pointer->cmds = strtok(buffer, " \n");
    pointer->args = strtok(NULL, "\n");
    return pointer->cmds, pointer->args;
}