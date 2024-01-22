#include "header/zivline.h"



char *cmdArray[] = {"echo", "help", "-", "ver", "start", "execute", "clr", "pause", "read", 
"write", "create", "exit", "zwrite", "run", "system", "moveto", "cd", "pd", "color", "bcolor", 
"makedir", "deldir", "crash", "poweroff", "process", "state", "copy", "delete", "reg", "startshell"};

static LONG WINAPI failureHandler(struct _EXCEPTION_POINTERS* exceptionInfo){
    fallbackShell(exceptionInfo);
    return 0;
}


static void segchecker(int signel){
    printf("Segmentation Fault in Externel Process\n");
    ExitThread(-1);
}

static DWORD WINAPI createNewThreadForCommandProcessing(LPVOID param) {
    
    SetUnhandledExceptionFilter(failureHandler);
    ziv* pointer = (ziv*)param;
    cmdExecute(pointer->current, pointer);
    ExitThread(0);    
    return 0;
}

static DWORD WINAPI createNewThreadForRunningExecutable(LPVOID param) {
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
    if(pointer->cmds[0] == 'z' && pointer->cmds[1] == 'v' && pointer->cmds[2] == 'a' && pointer->cmds[3] == 'p' && pointer->cmds[4] == 'i'){
        zvapiFunctionParser(pointer);
        return FALSE;
    }
    if(pointer->cmds[0] == ',' && pointer->cmds[1] == ','){
        HANDLE hThread = CreateThread(NULL, 0, createNewThreadForRunningExecutable, (LPVOID)pointer, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        return FALSE;
    }
    
    if(pointer->cmds[0] == '.' && pointer->cmds[1] == '/'){
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






