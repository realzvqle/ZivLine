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
            exitCleanup(0, pointer);
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
            printDir(pointer);
            break;
        case 17:
            listFiles(pointer);
            break;
        case 18:
            changeConsoleColor(pointer);
            break;
        case 19:
            changeBackGroundConsoleColor(pointer);
            break;
        case 20:
            newMakeDirectory(pointer);
            break;
        case 21:
            newDeleteDirectory(pointer);
            break;
        case 22:
            printf("(!) Message From 404oops\n\ngo fuck yourself\n");
            break;
        default:
            printf("%s Is The Incorrect\n", pointer->cmds);
            break;
    }
    return index;
}


