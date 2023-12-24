#include "header/zivline.h"



int main(int argc, char *argv[]){
    if(!argv[1]){
        printf("ZivLine [Version %0.1f]\n(c) zvqle, All rights reserved\n", VER);
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