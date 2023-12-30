@echo off

windres resources/res.rc -O coff -o resources/res.o

gcc -O1 -s resources/res.o src/*.c -o zivline.exe
start zivline.exe