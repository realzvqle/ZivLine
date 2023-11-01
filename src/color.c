#include "header/zivline.h"






void changeBackGroundConsoleColor(ziv *pointer){
    WORD color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
    if(!pointer->args) {
        printf("bcolor *color - changes background color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }
    if(strcmp(pointer->args, "red") == 0){
        color = BACKGROUND_RED;
        SetConsoleTextAttribute(hConsole, color); 
    } 
    else if(strcmp(pointer->args, "green")== 0){
        color = BACKGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "blue") == 0){
        color = BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "gray") == 0){
        color = BACKGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "white") == 0){
        color = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    } 
    
    else if(strcmp(pointer->args, "normal") == 0 ){
        WORD newAttributes = bufferInfo.wAttributes & ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        newAttributes &= ~FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, newAttributes);
        color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    }

    else {
        printf("bcolor *color - changes background color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }
    

    return;
}

void changeConsoleColor(ziv *pointer){
    WORD color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!pointer->args){
        printf("color *color - changes color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }
    if(strcmp(pointer->args, "red") == 0){
        color = FOREGROUND_RED;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "green")== 0){
        color = FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "blue") == 0){
        color = FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "gray") == 0){
        color = FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(strcmp(pointer->args, "white") == 0 ||strcmp(pointer->args, "normal") == 0 ){
        color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    }
    else{
        printf("color *color - changes color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }


    return;
}