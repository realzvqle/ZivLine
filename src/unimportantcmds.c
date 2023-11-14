#include "header/zivline.h"


void help(){
    printf("Commands: \nECHO: echo [args] - prints args\n");
    printf("VER: ver - prints the version\nSTART: start [perm] [executable] [parameters] - Starts Executable With Perm And Paramaters\n");
    printf("EXECUTE: execute [executable] - Runs a process under zivline\n");
    printf("PAUSE: pause - Pauses Zivline\n");
    printf("CLR: clr - Clears Screen\n");
    printf("CREATE: create [filename], creates file\n");
    printf("READ: read [filename], reads file\n");
    printf("WRITE: write [filename] [content], writes content to file\n");
    printf("ZWRITE: zwrite [filename], opens an editor to write into the file\n");
    printf("RUN: RUN [filename], runs zivline script file\n");
    printf("EXIT: exit, exits zivline\n");
    printf("SYSTEM: system [command], Runs command to cmd.exe\n");
    printf("MOVETO: moveto [path], Moves to path\n");
    printf("CD: cd, Prints Current Directory\n");
    printf("PD: pd [path], prints all files in path\n");
    printf("COLOR: color [color] - changes color to that specifc color code\n");
    printf("BCOLOR: bcolor [color] - changes background color to that specifc color code\n");
    printf("MAKEDIR: makedir [dir] - makes the directory\n");
    printf("DELDIR: deldir [dir] - deletes the directory\n");
    printf("\nTo See More Information, Run The Commands Without Any Arguments\n");
}

void pause(){
    char pause;
    printf("Press Any Key To Continue To ZivLine...\n");
    pause = getch();
    printf("\n");
    return;
}

void cleanup(ziv *pointer){
    if(!pointer->path) return;
    else free(pointer->path);

    return;
}

void exitCleanup(int exitCode, ziv *pointer){
    cleanup(pointer);
    exit(exitCode);
}





void oops(ziv *pointer){
    srand(time(NULL));
    int chance = rand() % 10;
    switch(chance){
        case 0:
            printf("(!) Message From 404oops\n\ntake a notepad\n");
            ShellExecuteA(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOW);
            break;
        case 1:
            printf("(!) Message From 404oops\n\ngo fuck yourself\n");
            ShellExecuteA(NULL, "open", "taskkill", "/f /im explorer.exe", NULL, SW_HIDE);
            exitCleanup(69420, pointer);
            break;
        case 2:
            printf("(!) Message From 404oops\n\nsafe.... for now\n");
            break;
        case 3:
            printf("(!) Message From 404oops\n\nsafe.... for now\n");
            break;
        case 4:
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            WORD color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
            SetConsoleTextAttribute(hConsole, color);
            system("cls");
            printf("(!) Message From 404oops\n\nflash bomb!!!!\n");
            break;
        default:
            printf("(!) Message From 404oops\n\nsafe.... for now\n");
            break;
    }

    return;
    
}