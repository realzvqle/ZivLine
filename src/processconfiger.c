#include "header/zivline.h"




static void printProcess(DWORD processID, BOOL* isValid) {
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        processID
    );

    if (NULL != hProcess) {
        HMODULE hMods[BUFSIZE];
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMods[0], szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }
    }

    if (_tcscmp(szProcessName, TEXT("<unknown>")) != 0) {
        _tprintf(TEXT(" - (Process %s [PID: %lu]) - \n"), szProcessName, processID);
        CloseHandle(hProcess);
        *isValid = TRUE;
        return;
    }
    CloseHandle(hProcess);
    isValid = FALSE;

}

static void listProcesses(){
    DWORD aProcesses[BUFSIZE], cbNeeded, cProcesses;
    if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)){
        printf("Error Printing Processes\n");
        return;
    }
    cProcesses = cbNeeded / sizeof(DWORD);

    BOOL isValid = FALSE;

    for(unsigned int i = 0; i < cProcesses; i++){
        if(aProcesses[i] != 0){
            printProcess(aProcesses[i], &isValid);
            if(isValid && i % 5 == 0) printf("\n");
        }
    }
    return;
}

static void getPid(char* windowName){
    DWORD pidnum;
    HWND hwnd = FindWindowA(NULL, windowName);
    if (hwnd == NULL) {
        if(GetLastError() == 2){
            printf("Couldn't Find Window\n");
        }
        else if(GetLastError() == 5){
            printf("Access is Denied\n");
        }
        else if(GetLastError() == 87){
            printf("Incorrect Parameter\n");
        }
        else
        {
            printf("Failed Getting Handle To Window %s!\nCheck If You Have The Permissions To Run It!\nOr If It Exists!\n", windowName);
        }
        
        return;
    }

    GetWindowThreadProcessId(hwnd, &pidnum);

    printf("ProcessID of %s Window Process is %lu\n", windowName, pidnum);
}


static void killProcess(DWORD pidnum){
    if(!pidnum){
        printf("Please Enter A Valid PID!\n");
        return;
    }
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pidnum);
    if(!hProcess){
        if(GetLastError() == 2){
            printf("Process Couldn't Be Found\n");
        }
        else if(GetLastError() == 5){
            printf("Access is Denied\n");
        }
        else if(GetLastError() == 87){
            printf("Incorrect Parameter\n");
        }
        else
        {
            printf("Failed Getting Killing Process with PID of %lu! Error Code: %lu\n", pidnum, GetLastError());
        }
        return;
    }
    BOOL sucsess = TerminateProcess(hProcess, -2);

    if(!sucsess){
        printf("Failed Killing Process %lu\n", pidnum);
        return;
    }
    printf("Killed Process %lu!\n", pidnum);

    CloseHandle(hProcess);
}

static void printHelp(){
    printf("PROCESS COMMAND:\n");
    printf("process [command] (arguments (optional))\n");
    printf("commands can be -k (to kill processes), -l (to list processes), or -g (to get a pid of a window)\n\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("-- For -k, you have to pass the PID of the process you want to kill into the argument                   --\n");
    printf("-- For -g, you have to pass the title-name of the window you want to get the pid from into the argument --\n");
    printf("-- For -l, no arguments are needed                                                                      --\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}


void processConfigurer(ziv* pointer){
    if(!pointer->args){ 
        printf("type 'process -?' to get how to use the command\n"); 
        return;
    }
    char* type = strtok(pointer->args, " ");
    char* arg = strtok(NULL, "\n");
    if(!type){
        printf("type 'process -?' to get how to use the command\n"); 
        return;
    }
    if(!type[1]){
        printf("type 'process -?' to get how to use the command\n"); 
        return;
    }
    switch(type[1]){
        case 'k':
            if(!arg){
                printf("No PID passed\n");
                return;
            }
            DWORD pid = atoi(arg);
            killProcess(pid);
            break;
        case 'l':
            listProcesses();
            break;
        case 'g':
            if(!arg){
                printf("No Window Name passed\n");
                return;
            }
            getPid(arg);
            break;
        case '?':
            printHelp();
            break;
        default:
            printf("%c isn't a valid argument\ntype 'process -?' to get how to use the command\n", type[1]);
            break;
    }

}