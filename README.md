# ZivLine
Welcome TO ZivLine, A Shell And Script Interperter For Microsoft Windows


# How To Use

 - To enter the Shell, Just Start The Executable
 - To Use The Interperter, Either go to the commandline and start ``zivline your-file-name.zls`` or enter the shell and type ``run your-file-name.zls`` (MUST BE IN SAME DIRECTORY AS THE SHELL!!!)



⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀









# Zivline Shell/Script Interpreter Documentation
The Documentaion Will Be Here, As I don't think it needs a full new page

# ECHO
Prints the provided arguments.

Syntax: echo *args

Example: ```echo Hello, World!``` <- Prints "Hello, World!"


# VER
Prints the version of Zivline.

Syntax: ver

# START
Starts an executable with specified permissions and parameters.

Syntax: start *perm *executable *parameters

Example: ``start user my_program.exe -d`` <- Starts my_program.exe with the -d parameter in user mode

``start admin my_program.exe -d`` <- Starts my_program.exe with the -d parameter in admin mode



# PAUSE
Pauses Zivline.

Syntax: pause

# CLR
Clears the screen.

Syntax: clr

# CREATE
Creates a new file with the specified filename.

Syntax: create *filename

Example: ``create my_file.txt``

# READ
Reads the contents of the specified file.

Syntax: read *filename

Example: ``read my_file.txt``

# WRITE
Writes content to the specified file.

Syntax: write *filename *content

Example: ``write my_file.txt This is some content``

# ZWRITE
Opens an editor to write into the specified file.

Syntax: zwrite *filename

Example: ``zwrite my_file.txt``

# RUN
Runs a Zivline script file.

Syntax: run *filename

Example: ``run my_script.zln``


# SYSTEM
Runs through cmd.

Syntax: SYSTEM *command

Example: ``system dir`` <- Runs dir from cmd.exe

# MOVETO
Moves The Directory To Another Directory.

Syntax: moveto *path

Example: ``moveto C:\Windows`` <- Moves To C:\Windows

# CD
Prints Current Directory

Syntax: cd

# PD
Prints Files In The Directory.

Syntax: pd *path

(if you moved outside the normal directory, you can type "pd" to print that directory)

Example: ``pd C:\Windows`` <- Prints All The Files In C:\Windows



# COLOR
Changes Font Color

Syntax: color *color


Example: ``color red`` <- changes it to red

ALL POSSIBLE COLORS:
    RED, GREEN, BLUE, GRAY, WHITE, NORMAL

# BCOLOR
Changes Background Color

Syntax: bcolor *color


Example: ``bcolor red`` <- changes background to red

ALL POSSIBLE COLORS:
    RED, GREEN, BLUE, GRAY, WHITE, NORMAL

# MAKEDIR
Makes A Directory

Syntax: makedir *dir


Example: ``makedir stuff`` <- makes a stuff directory

# DELDIR
Deletes A Directory

Syntax: deldir *dir


Example: ``deldir stuff`` <- deletes the directory

# KILL
Kills a process through the processID

Syntax: kill *pid


Example: ``kill 18189`` <- Kills The Process With The PID of 18189

# GETPID
Gets The PID of a Window (NOT FILENAME!!!!!)

Syntax: getpid *windowname


Example: ``getpid Untitled - Notepad`` <- Gets the pid of a new notepad window




# EXIT
Exits Zivline.

Syntax: exit
