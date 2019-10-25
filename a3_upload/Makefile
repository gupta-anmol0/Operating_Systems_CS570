#Makefile for Assignment 3
#Names : Anmol Deep Gupta and Alan Olvera
#Usernames : cssc0843 and cssc0842
#Red Ids: 823381384 and 818313984
#Class : CS570 Summer 2019
#Assignment : #3, emp
#Filename : Makefile

EXEC = emp

CC = gcc

CFLAGS = -pthread

all: clean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) -o $@ a3.c

clean:
	rm -f *.o $(EXEC)

