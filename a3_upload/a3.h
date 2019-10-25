/******************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIDs: 823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #3, Event Management Program
Filename: a3.h
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <time.h>

#define MAXITEMS 6				// maximum number of arguments allowed in command prompt

/********* prototype declarations of various functions used in a3.c ********/
void display_prompt();

void term_handler();

void term_handler();

void parse();							