@echo off

gcc src/main.c src/cli.c src/parser.c src/freader.c src/cmdchecker.c src/cmdexecute.c src/tolower.c -o zivline.exe