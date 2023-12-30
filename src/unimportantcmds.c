#include "header/zivline.h"


void help(){
    printf("Commands: \nECHO: echo [args] - prints args\n");
    printf("VER: ver - prints the version\nSTART: start [perm] [executable] [parameters] - Starts Executable With Perm And Paramaters\n");
    printf("EXECUTE: execute [executable] - Runs a process under zivline\n");
    printf("PAUSE: pause - Pauses Zivline\n");
    printf("CLR: clr - Clears Screen\n");
    printf("CREATE: create [filename], creates file\n");
    printf("READ: read [filename], reads file\n");
    printf("WRITE: write [filename] [content], writes content to file\n");
    printf("ZWRITE: zwrite [filename], opens an editor to write into the file\n");
    printf("RUN: RUN [filename], runs zivline script file\n");
    printf("EXIT: exit, exits zivline\n");
    printf("SYSTEM: system [command], Runs command to cmd.exe\n");
    printf("MOVETO: moveto [path], Moves to path\n");
    printf("CD: cd, Prints Current Directory\n");
    printf("PD: pd [path], prints all files in path\n");
    printf("COLOR: color [color] - changes color to that specifc color code\n");
    printf("BCOLOR: bcolor [color] - changes background color to that specifc color code\n");
    printf("MAKEDIR: makedir [dir] - makes the directory\n");
    printf("DELDIR: deldir [dir] - deletes the directory\n");
    printf("GETPID: getpid [Window Name] - Gets The Pid Of The Process\n");
    printf("KILL: kill [pid] - kills the process when supplied the processID\n");
    printf("COPY: copy [filename1] [filename2] - Copy First File To Second File\n");
    printf("DELETE: delete [filename] - Deletes The File\n");
    printf("REG: reg [dowhat] [hkey] [regpath] {valuename} (only for -w) {datatype} (only for -w) - Edits the registry");
    printf("\nTo See More Information, Run The Commands Without Any Arguments\n");
}

void pause(){
    char pause;
    printf("Press Any Key To Continue To ZivLine...\n");
    pause = getch();
    printf("\n");
    return;
}

void cleanup(ziv *pointer){
    free(pointer->path);
    return;
}

void exitCleanup(int exitCode, ziv *pointer){
    pointer->exit = true;
    printf("Exited With Exit Code %d\n", exitCode);
}





void oops(ziv *pointer){
    char* idk;
    strcpy(idk, "hi");
    return;
    
}

bool CheckAdmin() {
    BOOL isAdmin;
    SID_IDENTIFIER_AUTHORITY NTA = SECURITY_NT_AUTHORITY;
    PSID AdminGroup;
    AllocateAndInitializeSid(&NTA, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdminGroup);
    CheckTokenMembership(NULL, AdminGroup, &isAdmin);
    FreeSid(AdminGroup);
    return isAdmin;
}




