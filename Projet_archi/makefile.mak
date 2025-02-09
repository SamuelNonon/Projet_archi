all:
	gcc -o main.exe main.c scr/instruction.c scr/programme.c scr/read.c scr/operation.c -Iheaders -W