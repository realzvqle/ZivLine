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
        _tprintf(TEXT(" - (Process %s [PID: %u]) - \n"), szProcessName, processID);
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
    if(!windowName){
        printf("getpid [Window Name], Gets The Pid Of The Process\n(it isn't the name of the file its running from, but the actual window name)\n(example: to get the pid of wordpad, get the name of the window [ex: Document - WordPad] instead of wordpad.exe)\n");
        return;
    }
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

    printf("ProcessID of %s Window Process is %d\n", windowName, pidnum);
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
            printf("Failed Getting Killing Process with PID of %d! Error Code: %d\n", pidnum, GetLastError());
        }
        return;
    }
    BOOL sucsess = TerminateProcess(hProcess, -2);

    if(!sucsess){
        printf("Failed Killing Process %d\n", pidnum);
        return;
    }
    printf("Killed Process %d!\n", pidnum);

    CloseHandle(hProcess);
}




void processConfigurer(ziv* pointer){
    if(!pointer->args){ 
        printf("No Arguments passed\n"); 
        return;
    }
    char* type = strtok(pointer->args, " ");
    char* arg = strtok(NULL, "\n");
    if(!type[1]){
        printf("No Argument Passed\n");
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
        default:
            printf("%c isn't a valid argument\n", type[1]);
            break;
    }

}