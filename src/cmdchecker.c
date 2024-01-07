#include "header/zivline.h"



char *cmdArray[] = {"echo", "help", "-", "ver", "start", "execute", "clr", "pause", "read", 
"write", "create", "exit", "zwrite", "run", "system", "moveto", "cd", "pd", "color", "bcolor", 
"makedir", "deldir", "crash", "kill", "getpid", "state", "copy", "delete", "reg", "startshell"};

void failureHandler(int signal){
    fprintf(stderr, "ZivLine Has Encountered An Error, Please Report This To zvqle!\n");
    ExitThread(-1);
}

DWORD WINAPI createNewThreadForCommandProcessing(LPVOID param) {
    signal(SIGSEGV, fallbackShell);
    ziv* pointer = (ziv*)param;
    cmdExecute(pointer->current, pointer);
    ExitThread(0);    
    return 0;
}

DWORD WINAPI createNewThreadForRunningExecutable(LPVOID param) {
    signal(SIGSEGV, failureHandler);
    ziv* pointer = (ziv*)param;
    startExecute(pointer);
    ExitThread(0);    
    return 0;
}



bool cmdChecker(ziv *pointer){
    bool foundCommand = false;
    int cmdSize = sizeof(cmdArray)/sizeof(cmdArray[0]);
    if(!pointer->cmds) return false;
    if(pointer->cmds[0] == ',' || pointer->cmds[1] == ','){
        HANDLE hThread = CreateThread(NULL, 0, createNewThreadForRunningExecutable, (LPVOID)pointer, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        return FALSE;
    }
    if(pointer->cmds[0] == '.' || pointer->cmds[1] == '/'){
        printf("To run an executable, you must do ',,' instead of ./\n");
        return FALSE;
    }
    toLowerCase(pointer->cmds);
    for(int i = 0; i < cmdSize; i++){
        if(strcmp(pointer->cmds, cmdArray[i]) == 0){
            pointer->current = i;
            HANDLE hThread = CreateThread(NULL, 0, createNewThreadForCommandProcessing, (LPVOID)pointer, 0, NULL);
            WaitForSingleObject(hThread, INFINITE);
            return true;
        }
    }
    printf("%s is the wrong command, please type \"help\" to see a list of cmds\nOr start an executable using ',,'\n", pointer->cmds);
    return false;
}






