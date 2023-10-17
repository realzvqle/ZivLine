#include "header\zivline.h"



bool fileRead(ziv *pointer){
    if(!pointer->args){
        printf("read: read *filename, opens a handle to filename and reads it\n");
        return FALSE;
    }
    FILE *fp;
    
    char buffer[BUFSIZE];
    fp = fopen(pointer->args, "r");
    if(!fp){
        perror("Error Reading File\n");
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
    FILE *fp;
    
    fp = fopen(pointer->args, "w");
    fprintf(fp, " ");
    fclose(fp);

}


bool fileWrite(ziv *pointer){
    if(!pointer->args){
        printf("write: write *filename *content, opens a handle to filename and writes content to it\n");
        return FALSE;
    }
    char *filename = strtok(pointer->args, " \n");
    char *content = strtok(NULL, "\n");
    FILE *fp;
    
    fp = fopen(filename, "w");
    fprintf(fp, "%s\n", content);
    fclose(fp);
}

bool fileWriteAdvanced(ziv *pointer){
    if(!pointer->args){
        printf("Zwrite: zwrite *filename, opens a handle to filename and edits it\n");
        return FALSE;
    }
    char *filename = strtok(pointer->args, " \n");
    char *content = strtok(NULL, "\n");

    char buffer[BUFSIZE];
    bool loop = true;
    int line = 0;
    FILE *fp;
    fp = fopen(filename, "w");
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

