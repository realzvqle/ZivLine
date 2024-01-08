#include "header/zivline.h"



char *cmdArray[] = {"echo", "help", "-", "ver", "start", "execute", "clr", "pause", "read", 
"write", "create", "exit", "zwrite", "run", "system", "moveto", "cd", "pd", "color", "bcolor", 
"makedir", "deldir", "crash", "kill", "getpid", "state", "copy", "delete", "reg", "startshell"};

LONG WINAPI failureHandler(struct _EXCEPTION_POINTERS* exceptionInfo){
    fallbackShell(exceptionInfo);
}


void segchecker(int signel){
    printf("Segmentation Fault\n");

    ExitThread(-1);
}

DWORD WINAPI createNewThreadForCommandProcessing(LPVOID param) {
    
    SetUnhandledExceptionFilter(failureHandler);
    ziv* pointer = (ziv*)param;
    cmdExecute(pointer->current, pointer);
    ExitThread(0);    
    return 0;
}

DWORD WINAPI createNewThreadForRunningExecutable(LPVOID param) {
    signal(SIGSEGV, segchecker);
    ziv* pointer = (ziv*)param;
    startExecute(pointer);
    ExitThread(0);    
    return 0;
}



BOOL cmdChecker(ziv *pointer){
    BOOL foundCommand = FALSE;
    int cmdSize = sizeof(cmdArray)/sizeof(cmdArray[0]);
    if(!pointer->cmds) return FALSE;
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
            return FALSE;
        }
    }
    printf("%s is the wrong command, please type \"help\" to see a list of cmds\nOr start an executable using ',,'\n", pointer->cmds);
    return FALSE;
}






