#include "header/zivline.h"



int WINAPI cmdExecute(int index, ziv *pointer){
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
            startFileReaderOnShell(pointer);
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
            if(pointer->state != 9){
                printf("This Is A Debug-Mode function, Please Enable Debug-Mode To Run This Command\n");
                break;
            }
            oops(pointer);
            break;
        case 23:
            break;
        case 24:
            processConfigurer(pointer);
            break;
        case 25:
            break;
        case 26:
            copyFile(pointer);
            break;
        case 27:
            removeFile(pointer);
            break;
        case 28: 
            editReg(pointer);
            break;
        case 29:
            cli clipointer;
            startShell(&clipointer);
            break;
        default:
            printf("%s Is Wrong Command! (!)\n", pointer->cmds);
            break;
    }
    return index;
}


