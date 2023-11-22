@echo off

windres resources/res.rc -O coff -o resources/res.o

gcc resources/res.o src/main.c src/cli.c src/parser.c src/freader.c src/cmdchecker.c src/cmdexecute.c src/tolower.c src/unimportantcmds.c src/startExec.c src/fileio.c src/dir.c src/color.c src/makedir.c src/runzls.c src/clrscr.c src/processconfiger.c -o zivline.exe
start zivline.exe