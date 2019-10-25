#Makefile for Assignment 2
#Names : Anmol Deep Gupta and Alan Olvera
#Usernames : cssc0843 and cssc0842
#Red Ids: 823381384 and 818313984
#Class : CS570 Summer 2019
#Assignment : #2, PAM
#Filename : Makefile

EXEC = pam

CC = gcc

CFLAGS = -Wall

all: clean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) -o $@ a2.c

clean:
	rm -f *.o $(EXEC)

