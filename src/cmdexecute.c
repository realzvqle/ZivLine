#include "header/zivline.h"

int cmdExecute(int index, ziv *pointer){
    switch(index){
        case 0:
            printf("%s\n", pointer->args);
            break;
        case 1:
            help();
            break;
        case 2:
            break;
        case 3:
            printf("ZivLine [Version %0.1f]\n", VER);
            break;
        case 4:
            Start(pointer);
            break;
        case 5:
            StartProcess(pointer);
            break;
        default:
            printf("%s Is The Incorrect Comamnd\n", pointer->cmds);
            break;
    }
    return index;
}


