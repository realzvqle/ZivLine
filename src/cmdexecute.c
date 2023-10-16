#include "header/zivline.h"


int cmdExecute(int index, ziv *pointer){
    switch(index){
        case 0:
            printf("%s\n", pointer->args);
            break;
        case 1:
            printf("Welcome To ZivLine!\n");
            break;
        case 2:
            break;
        default:
            printf("%s Is The Incorrect Comamnd\n", pointer->cmds);
            break;
    }
    return index;
}

