#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <direct.h>
#include <time.h>
#include <signal.h>


#define BUFSIZE 4096
#define VER 0.7





typedef struct{
    char buffer[BUFSIZE];
    char *fileName;
    FILE *fp;
} freader;

typedef struct{
    char buffer[BUFSIZE];
} cli;

typedef struct{
    char *args;
    char *cmds;
    char *path;
    int current;
    bool exit;
} ziv;






void cleanup(ziv *pointer);
bool startCLI(cli *clipointer);
bool startFileReader(freader *fpointer);
int WINAPI cmdExecute(int index, ziv *pointer);
char* cmdParser(char buffer[], ziv *pointer);
bool cmdChecker(ziv *pointer);
char *toLowerCase(char *string);
void execute_command(const char *cmd, ziv *pointer);
void help();
void Start(ziv *pointer);
void StartProcess(ziv *pointer);
void pause();
bool fileRead(ziv *pointer);
bool fileWrite(ziv *pointer);
bool fileCreate(ziv *pointer);
bool fileWriteAdvanced(ziv *pointer);
bool moveDirectory(ziv *pointer);
bool listFiles(ziv *pointer);
void changeConsoleColor(ziv *pointer);
void changeBackGroundConsoleColor(ziv *pointer);
void exitCleanup(int exitCode, ziv *pointer);
void newMakeDirectory(ziv *pointer);
void newDeleteDirectory(ziv *pointer);
void printDir(ziv *pointer);
void oops(ziv *pointer);
char* getDir();
bool startFileReaderOnShell(ziv *pointer);
void clrscr();
void KillProcess(ziv *pointer);
void GetPid(ziv *pointer);
void startExecute(ziv *pointer);
void copyFile(ziv *pointer);
BOOL removeFile(ziv *pointer);
void editReg(ziv *pointer);
bool CheckAdmin();
BOOL StartProcessA(char* cmd, char* args);
void fallbackShell();
