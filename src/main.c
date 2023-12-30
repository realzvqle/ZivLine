#include "header/zivline.h"



int main(int argc, char *argv[]){
    if(!argv[1]){
        printf("----------------------------------\n");
        printf("| ZivLine [Version %0.1f]          |\n", VER);
        printf("| (c) zvqle, All rights reserved |\n");
        printf("----------------------------------\n");

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