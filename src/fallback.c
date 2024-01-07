#include "header/zivline.h"

extern ziv pointer;
extern char *cmdArray[];


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
    printf("ZIVLINE HAS ENCOUNTERED AN FAILURE, PLEASE REPORT THIS TO ZVQLE\n");
    FILE* fp;
    char title[9];
    char state[BUFSIZE];
    sprintf(title, "Failure -> Zivline Crash. OS signal -> %d", signel);
    sprintf(state, "LOG:\n - PATH - %s\n - COMMAND - %s\n - ARGUMENT - %s\n - FAILED COMMAND - %s\n - POSITION OF COMMAND - %d\n - ISEXIT - %d\n", pointer.path, pointer.cmds, pointer.args, cmdArray[pointer.current], pointer.current, pointer.exit);
    fp = fopen("C:\\ProgramData\\ZivlineLog.txt", "w");
    if(!fp){
        printf("Failed Writing Log\n");
        fclose(fp);
        goto contin;
    }
    fprintf(fp, "%s\n\n", title);
    fprintf(fp, "%s", state);
    fclose(fp);
    printf("WROTE LOG IN C:\\ProgramData\\ZivlineLog.txt\n");
contin:
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