@echo off

gcc src/main.c src/cli.c src/parser.c src/freader.c src/cmdchecker.c src/cmdexecute.c src/tolower.c src/unimportantcmds.c src/startExec.c -o zivline.exe
start zivline.exe