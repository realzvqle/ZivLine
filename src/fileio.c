#include "header\zivline.h"



bool fileRead(ziv *pointer){
    if(!pointer->args){
        printf("read: read *filename, opens a handle to filename and reads it\n");
        return FALSE;
    }
    FILE *fp;
    char path[BUFSIZE] = "";
    if(!pointer->path) strcpy(path, pointer->args);
    else{
        Sleep(500);
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, pointer->args);
    }

    char buffer[BUFSIZE];
    fp = fopen(path, "r");
    if(!fp){
        perror("fopen");
        return FALSE;
    }
    while(fgets(buffer, BUFSIZE, fp)){
        strtok(buffer, "\n");
        printf("%s\n", buffer);
    }
    fclose(fp);
    return TRUE;
}


bool fileCreate(ziv *pointer){
    if(!pointer->args){
        printf("create: create *filename, Creates The File\n");
        return FALSE;
    }
    char path[BUFSIZE] = "";
    if(!pointer->path) strcpy(path, pointer->args);
    else{
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, pointer->args);
    }
    FILE *fp;
    
    fp = fopen(path, "w");
     if (fp == NULL) {
        perror("fopen");
        return false;
    }
    fclose(fp);

}


bool fileWrite(ziv *pointer){
    if(!pointer->args){
        printf("write: write *filename *content, opens a handle to filename and writes content to it\n");
        return FALSE;
    }

    char *filename = strtok(pointer->args, " \n");
    char *content = strtok(NULL, "\n");
    char path[BUFSIZE] = "";
    if(!pointer->path) strcpy(path, filename);
    else{
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, filename);
    }

    FILE *fp;
    
    fp = fopen(path, "a");
     if(!fp){
        perror("fopen");
        return FALSE;
    }
    fprintf(fp, "%s\n", content);
    fclose(fp);
}

bool fileWriteAdvanced(ziv *pointer){
    if(!pointer->args){
        printf("Zwrite: zwrite *filename, opens a handle to filename and edits it\n");
        return FALSE;
    }

    char path[BUFSIZE] = "";
    if(!pointer->path) strcpy(path, pointer->args);
    else{
        Sleep(500);
        strcpy(path, pointer->path);
        strcat(path, "\\");
        strcat(path, pointer->args);
    }

    char buffer[BUFSIZE];
    bool loop = true;
    int line = 0;
    FILE *fp;
    if(!fp){
        perror("fopen");
        return FALSE;
    }
    fp = fopen(path, "a");
    while(loop){
        printf("%d ~ ", line);
        fgets(buffer, BUFSIZE, stdin);
        strtok(buffer, "\n");
        if(strcmp(buffer, "-:quit") == 0){
            break;
        }
        line++;
        fprintf(fp, "%s\n", buffer);
    }
    //fprintf(fp, "%s\n", content);
    fclose(fp);
}

