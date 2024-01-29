#define _CRT_SECURE_NO_WARNINGS
#include "header/zivline.h"

ziv pointer;


int main(int argc, char *argv[]){
    if(!argv[1]){
        if(checkIfFileExists("init.zls") == TRUE){
            freader pointer;
            pointer.fileName = "init.zls";
            startFileReader(&pointer);
        }
        else if(checkIfFileExists("C:\\ProgramData\\init.zls") == TRUE){
            freader pointer;
            pointer.fileName = "C:\\ProgramData\\init.zls";
            startFileReader(&pointer);
        }
        else{
            printf("----------------------------------\n");
            printf("| ZivLine [Version %0.1f]          |\n", VER);
            printf("| (c) zvqle, All rights reserved |\n");
            printf("----------------------------------\n");
        }
        

        cli pointer;
        startCLI(&pointer);
    }
    else {
        freader pointer;
        pointer.fileName = argv[1];
        startFileReader(&pointer);
    }
    
    return 0;
}