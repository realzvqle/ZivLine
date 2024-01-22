#include "header/zivline.h"
#include <DbgHelp.h>

extern ziv pointer;
extern char *cmdArray[];

static BOOL createMemoryDump(char* filename){
    HANDLE pHandle = GetCurrentProcess();
    if(!pHandle){
        printf("Cannot Create Handle For Process\n");
        return FALSE;
    }
    HANDLE dumpFile = CreateFile(filename, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(!dumpFile){
        printf("Cannot Create File For Dump\n");
        return FALSE;
    }
    MiniDumpWriteDump(pHandle, GetCurrentProcessId(), dumpFile, MiniDumpWithFullMemory, NULL, NULL, NULL);
    CloseHandle(dumpFile);
    return TRUE;
}



static BOOL createLog(char* fileName, struct _EXCEPTION_POINTERS* exceptionInfo){
    FILE* fp;
    char title[BUFSIZE];
    char state[BUFSIZE];
    char add[BUFSIZE];
    char code[BUFSIZE];
    sprintf(title, "Failure -> Zivline Crash");
    sprintf(state, "LOG:\n - PATH - %s\n - COMMAND - %s\n - ARGUMENT - %s\n - FAILED COMMAND - %s\n - POSITION OF COMMAND - %d\n - ISEXIT - %d\n", 
    pointer.path, 
    pointer.cmds, 
    pointer.args, 
    cmdArray[pointer.current], 
    pointer.current, 
    pointer.exit);
    sprintf(add, "Exception Address in 0x%1llx\n", (unsigned long long)exceptionInfo->ExceptionRecord->ExceptionAddress);
    sprintf(code, "Exception Code in 0x%1lx\n", (DWORD)exceptionInfo->ExceptionRecord->ExceptionCode);

    fp = fopen(fileName, "w");
    if(!fp){
        printf("Failed Writing Log\n");
        return FALSE;
    }
    fprintf(fp, "%s\n\n", title);
    fprintf(fp, "%s", state);
    fprintf(fp, "%s", add);
    fprintf(fp, "%s", code);
    fclose(fp);
    return TRUE;

}

static void setupRecoveryMode(struct _EXCEPTION_POINTERS* exceptionInfo){
    
    printf("Writing Log in C:\\ProgramData\\ZivlineLog.txt\n");
    createLog("C:\\ProgramData\\ZivlineLog.txt", exceptionInfo);
    printf("Wrote Log IN C:\\ProgramData\\ZivlineLog.txt\n");

    printf("Writing Dump in C:\\ProgramData\\ZivLineCrashDump.dmp\n");
    createMemoryDump("C:\\ProgramData\\ZivLineCrashDump.dmp");
    printf("Wrote Dump in C:\\ProgramData\\ZivLineCrashDump.dmp\n");

    return;
    
}

static int recoveryProcessor(char* firstarg, char* secondarg){
    if(!firstarg){
        return -2;
    }
    firstarg = toLowerCase(firstarg);
    if(strcmp(firstarg, "exit") == 0){
        ExitThread(0);
    }
    if(strcmp(firstarg, "debugstate") == 0){
        printf("LOG:\n - PATH - %s\n - COMMAND - %s\n - ARGUMENT - %s\n - POSITION OF COMMAND - %s\n - CURRENT - %d\n", pointer.path, pointer.cmds, pointer.args, cmdArray[pointer.current], pointer.current);
    }
    // if(strcmp(firstarg, "resetstate") == 0){
    //     pointer.path = "EMPTYSTRING";
    //     pointer.cmds = NULL;
    //     pointer.args = NULL;
    //     pointer.current = 0;
    //     pointer.exit = FALSE;
    //     printf("Fully Reset ZivLine State - To return to the shell, type 'exit'\n");
    // }
    if(strcmp(firstarg, "help") == 0){
        printf("Recovery Commands: \ndebugstate: prints the state of zivline\nexit: exits recovery-mode and enters back to zivline\nleave: leaves zivline\n\n");
    }
    if(strcmp(firstarg, "leave") == 0){
        exit(0);
    }


    return 0;
    
}






void fallbackShell(struct _EXCEPTION_POINTERS* exceptionInfo){
    printf("ZivLine Has Crashed\n");
    printf("Exception Code is 0x%1lx\n", exceptionInfo->ExceptionRecord->ExceptionCode);
    printf("Exception Address in 0x%1llx\n", (unsigned long long)exceptionInfo->ExceptionRecord->ExceptionAddress);
    setupRecoveryMode(exceptionInfo);
    printf("STARTING RECOVERY MODE........\n");
    Sleep(2000);
    char buffer[BUFSIZE];
    char* first;
    char* second;
    printf("-------------------------------------------------------------------------------\n");
    printf("| ZIVLINE RECOVERY MODE                                                       |\n");
    printf("| TYPE HELP FOR COMMANDS - TYPE EXIT TO RETURN BACK TO ZIVLINE                |\n");
    printf("| TYPE DEBUGSTATE TO GET THE CURRENT STATE OF ZIVLINE WHEN THE CRASH HAPPENED |\n");
    printf("-------------------------------------------------------------------------------\n\n");

    while(1){
    GOBACK:
        printf("--> ");
        fgets(buffer, BUFSIZE, stdin);
        strtok(buffer, "\n");
        first = strtok(buffer, " \n");
        second = strtok(NULL, "\n");
        int returne = recoveryProcessor(first, second);
        if(returne == 98) return;
    }
}