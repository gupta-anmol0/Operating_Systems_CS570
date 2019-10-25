#Makefile for Assignment 1
#Names: Anmol Deep Gupta and Alan Olvera
#Usernames: cssc0843 and cssc0842
#RedIds:  823381384 and 818313984
#Class: CS570 Summer 2019
#Assignment: #1, Multiple Thread Management
#Filename: Makefile


EXEC = player
CC = gcc
CFLAGS = -pthread
 
all: clean $(EXEC)


$(EXEC):
	$(CC) $(CFLAGS) -o $@ a1.c

clean:
	rm -f $(EXEC) STACK.txt
