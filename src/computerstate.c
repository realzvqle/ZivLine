#include "header/zivline.h"

typedef enum _SHUTDOWN_ACTION
{
    ShutdownNoReboot,
    ShutdownReboot,
    ShutdownPowerOff,
    ShutdownRebootForRecovery
} SHUTDOWN_ACTION;

typedef NTSTATUS(WINAPI *PNtShutdownSystem)(ULONG);


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


static void forceShutdown(char* type, char* isValid){
    if(strcmp(isValid, "1") != 0) return;
     if (!giveShutDownPerms()) {
        printf("Failed to obtain shutdown privileges\n");
        return;
    }
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        printf("Failed Opening NTDLL\n");
        return;
    }
    PNtShutdownSystem NTShutdown = (PNtShutdownSystem)GetProcAddress(ntdll, "NtShutdownSystem");
    if(!NTShutdown){
        printf("Failed Extracting Function From NTDLL\n");
        return;
    }
    switch(type[1]){
        case 'r':
            NTSTATUS restartStatus = NTShutdown(1);
            if(!NT_SUCCESS(restartStatus)){
                printf("Failed Shutting Down Windows, Error Code %lx\n", restartStatus);
            }
            break;

        case 's':
            NTSTATUS shutdownStatus = NTShutdown(0);
            if(!NT_SUCCESS(shutdownStatus)){
                printf("Failed Shutting Down Windows, Error Code %lx\n", shutdownStatus);
            }
            break;
        case 'y':
            NTSTATUS recStatus = NTShutdown(3);
            if(!NT_SUCCESS(recStatus)){
                printf("Failed Shutting Down Windows, Error Code %lx\n", recStatus);
            }
            break;
        case '?':
            printf("poweroff [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown.\nisImmediate can be 1 if true, else 0 or leave empty\n");
            break;
        default:
            printf("Incorrect Argument, Use -s to shutdown or -r to restart\n");
            break;
    }
    
}


void shutdownWindows(ziv *pointer){
    char* type = strtok(pointer->args, " ");
    char* isImmediate = strtok(NULL, "\n");
    if(!giveShutDownPerms()){
        return;
    }
    if(!type){
        printf("poweroff [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown, -l to logoff (if isImmediate isn't 1).\nisImmediate can be 1 if true, else 0 or empty\n");
    }
    if(isImmediate){
        forceShutdown(type, isImmediate);
        return;
    }
    
    switch(type[1]){
        case 'r':
            if(!ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_MAJOR_SYSTEM)){
                printf("Cannot Restart Windows, Error Code %lu\n", GetLastError());
            }
            break;
        case 's':
            if(!ExitWindowsEx(EWX_SHUTDOWN, SHTDN_REASON_MAJOR_SYSTEM)){
                printf("Cannot Restart Windows, Error Code %lu\n", GetLastError());
            }
            break;
        case 'l':
            if(!ExitWindowsEx(EWX_RESTARTAPPS, SHTDN_REASON_MAJOR_SYSTEM)){
                printf("Cannot Restart Windows, Error Code %lu\n", GetLastError());
            }
            break;
        case '?':
            printf("poweroff [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown, -l to logoff\nisImmediate can be 1 if true, else 0 or leave empty\n");
            break;
        default:
            printf("Incorrect Argument, Use -s to shutdown or -r to restart\n");
            break;
    }
}


