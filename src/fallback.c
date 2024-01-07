#include "header/zivline.h"
#include <DbgHelp.h>

extern ziv pointer;
extern char *cmdArray[];

BOOL createMemoryDump(char* filename){
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

BOOL createLog(char* fileName){
    FILE* fp;
    char title[BUFSIZE];
    char state[BUFSIZE];
    sprintf(title, "Failure -> Zivline Crash. OS signal -> %d", 11);
    sprintf(state, "LOG:\n - PATH - %s\n - COMMAND - %s\n - ARGUMENT - %s\n - FAILED COMMAND - %s\n - POSITION OF COMMAND - %d\n - ISEXIT - %d\n", 
    pointer.path, 
    pointer.cmds, 
    pointer.args, 
    cmdArray[pointer.current], 
    pointer.current, 
    pointer.exit);
    fp = fopen(fileName, "w");
    if(!fp){
        printf("Failed Writing Log\n");
        return FALSE;
    }
    fprintf(fp, "%s\n\n", title);
    fprintf(fp, "%s", state);
    fclose(fp);
    return TRUE;

}

void setupRecoveryMode(){
    
    printf("Writing Log in C:\\ProgramData\\ZivlineLog.txt\n");
    createLog("C:\\ProgramData\\ZivlineLog.txt");
    printf("Wrote Log IN C:\\ProgramData\\ZivlineLog.txt\n");

    printf("Writing Dump in C:\\ProgramData\\ZivLineCrashDump.dmp\n");
    createMemoryDump("C:\\ProgramData\\ZivLineCrashDump.dmp");
    printf("Wrote Dump in C:\\ProgramData\\ZivLineCrashDump.dmp\n");

    return;
    
}

int recoveryProcessor(char* firstarg, char* secondarg, int signel){
    firstarg = toLowerCase(firstarg);
    if(!firstarg){
        return -2;
    }
    if(strcmp(firstarg, "exit") == 0){
        ExitThread(0);
    }
    if(strcmp(firstarg, "signel") == 0){
        printf("--%d--\n", signel);
    }
    if(strcmp(firstarg, "exit") == 0){
        printf("--%d--\n", signel);
    }
    if(strcmp(firstarg, "debugstate") == 0){
        printf("LOG:\n - PATH - %s\n - COMMAND - %s\n - ARGUMENT - %s\n - FAILED COMMAND - %s\n - POSITION OF COMMAND - %d\n - ISEXIT - %d\n", pointer.path, pointer.cmds, pointer.args, cmdArray[pointer.current], pointer.current, pointer.exit);
    }
    if(strcmp(firstarg, "resetstate") == 0){
        pointer.path = "EMPTYSTRING";
        pointer.cmds = NULL;
        pointer.args = NULL;
        pointer.current = 0;
        pointer.exit = FALSE;
        printf("Fully Reset ZivLine State - To return to the shell, type 'exit'\n");
    }
    if(strcmp(firstarg, "help") == 0){
        printf("Recovery Commands: \ndebugstate: prints the state of zivline\nresetstate: resets zivlines state to a stable state\nexit: exits recovery-mode and enters back to zivline\nsignel: Returns The Latest OS Signel \nleave: leaves zivline\n\n");
    }
    if(strcmp(firstarg, "leave") == 0){
        exit(0);
    }


    return 0;
    
}






void fallbackShell(int signel){
    setupRecoveryMode();
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
        printf("--> ");
        fgets(buffer, BUFSIZE, stdin);
        strtok(buffer, "\n");
        first = strtok(buffer, " \n");
        second = strtok(NULL, "\n");
        int returne = recoveryProcessor(first, second, signel);
        if(returne == 98) return;
    }
}