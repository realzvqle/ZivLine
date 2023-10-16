#include "header/zivline.h"



char *toLowerCase(char *string){
    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }
    return string;
}