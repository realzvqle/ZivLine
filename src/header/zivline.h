#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE 4096
#define VER 0.1




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
} ziv;




bool startCLI(cli *clipointer);
bool startFileReader(freader *fpointer);
int cmdExecute(int index, ziv *pointer);
char* cmdParser(char buffer[], ziv *pointer);
bool cmdChecker(ziv *pointer);
char *toLowerCase(char *string);
void execute_command(const char *cmd, ziv *pointer);
void help();
void Start(ziv *pointer);
void StartProcess(ziv *pointer);
