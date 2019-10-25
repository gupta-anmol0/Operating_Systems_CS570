/*****************************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIds:  823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #2, PAM
Filename: a2.c
****************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define STORAGE 255						// maximum number of characters in each word typed on command line
#define MAXITEMS 100					// maximum number of items the prompt can take

void display_prompt();					// for displaying the prompt

void parse();							// parse routine will read in the input from stdin and tokenize the input string

void piperoutine();						// piperoutine will be called if a pipe is encountered

void execute_routine();


