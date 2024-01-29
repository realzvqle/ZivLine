#include "header/zivline.h"




BOOL checkIfFileExists(char* fileName){
    FILE* fp = fopen(fileName, "r");
    if(!fp){
        return FALSE;
    }
    fclose(fp);
    return TRUE;
}