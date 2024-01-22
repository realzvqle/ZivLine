// fUCK VSCODE AND ITS C LSP IT SUCKS SO BAD SNJSKBHRJJENENE



#include "header/zivline.h"
#include <handleapi.h>
#include <processthreadsapi.h>
#include <securitybaseapi.h>
#include <winbase.h>
#include <winnt.h>

static BOOL giveShutDownPerms(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)){
        printf("Cannot Open Process Token, Error Code %lu\n", GetLastError());
        return FALSE;
    }
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, (PLUID)&tkp.Privileges);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0)){
        printf("Cannot Change Token Privlages, Error Code %lu\n", GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }
    CloseHandle(hToken);
    return TRUE;
}



void shutdownWindows(ziv *pointer){
    char* type = strtok(pointer->args, " ");
    char* isImmediate = strtok(NULL, "\n");
    if(!giveShutDownPerms()){
        return;
    }
    if(!type){
        printf("poweroff [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown. isImmediate can be 1 if true, else 0 or empty\n");
    }
    
    switch(type[1]){
        case 'r':
            if(!ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_MAJOR_SYSTEM)){
                printf("Cannot Restart Windows, Error Code %lu\n", GetLastError());
            }
            break;

    }
}


