#include "header/zivline.h"




bool startFileReader(freader *fpointer){
    ziv pointer;
    pointer.path = (char*)malloc(BUFSIZE);
    strcpy(pointer.path, "EMPTYSTRING");
    fpointer->fp = fopen(fpointer->fileName, "r");
    if(!fpointer->fp){
        printf("Failed Opening File\n");
        return false;
    }
    pointer.exit = false;
    while(fgets(fpointer->buffer, BUFSIZE, fpointer->fp)){
        if(pointer.exit) break;
        strtok(fpointer->buffer, "\n");
        pointer.cmds, pointer.args = cmdParser(fpointer->buffer, &pointer);
        cmdChecker(&pointer);
    }
    if(! pointer.exit) cleanup(&pointer);
    fclose(fpointer->fp);
}