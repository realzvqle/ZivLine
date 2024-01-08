#include "header/zivline.h"



void GetPid(ziv *pointer){
    if(!pointer->args){
        printf("getpid [Window Name], Gets The Pid Of The Process\n(it isn't the name of the file its running from, but the actual window name)\n(example: to get the pid of wordpad, get the name of the window [ex: Document - WordPad] instead of wordpad.exe)\n");
        return;
    }
    DWORD pidnum;
    HWND hwnd = FindWindowA(NULL, pointer->args);
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
            printf("Failed Getting Handle To Window %s!\nCheck If You Have The Permissions To Run It!\nOr If It Exists!\n", pointer->args);
        }
        
        return;
    }

    GetWindowThreadProcessId(hwnd, &pidnum);

    printf("ProcessID of %s Window Process is %d\n", pointer->args, pidnum);
}


void KillProcess(ziv *pointer){
    if(!pointer->args){
        printf("kill [pid], kills the process when supplied the processID of the process\n");
        return;
    }
    DWORD pidnum = atoi(pointer->args);
    if(!pidnum){
        printf("Please Enter A Valid PID!\n");
        return;
    }
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pidnum);
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
