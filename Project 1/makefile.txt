#makefile for project1

C=gcc

FLAGS= -g -c  -Wall

myshell: myshell.o parse.o
	 $(C) myshell.o parse.o -o myshell

myshell.o: myshell.c parse.h
	   $(C) $(FLAGS) myshell.c

parse.o: parse.c parse.h
	 $(C) $(FLAGS) parse.c 

clean: 
	rm *.o myshell  
