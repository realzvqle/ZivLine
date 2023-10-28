#include "header/zivline.h"



int main(int argc, char *argv[]){
    if(!argv[1]){
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