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
        case 6:
            clrscr();
            break;
        case 7:
            pause();
            break;
        case 8:
            fileRead(pointer);
            break;
        case 9:
            fileWrite(pointer);
            break;
        case 10:
            fileCreate(pointer);
            break;
        case 11:
            exit(0);
            break;
        case 12:
            fileWriteAdvanced(pointer);
            break;
        case 13:
            freader fptr;
            fptr.fileName = pointer->args;
            startFileReader(&fptr);
            break;
        case 14:
            system(pointer->args);
            break;
        case 15:
            moveDirectory(pointer);
            break;
        case 16:
            if(!pointer->path) break;
            printf("Current Directory Is %s\n", pointer->path);
            break;
        case 17:
            listFiles(pointer);
            break;
        default:
            printf("%s Is The Incorrect\n", pointer->cmds);
            break;
    }
    return index;
}


