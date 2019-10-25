/******************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIDs: 823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #1, Multiple Thread Management
Filename: README 
******************************************/
CLASS ACCOUNT USED: cssc0843

README contains:
-Assignment #1 Prompt
-Files Included
-Compilation Instructions
-Design Decisions
-Objectives Learned

******************************************* 

Prompt:
Design, develop, and test a program where four "card players" will run, each in their
own thread, simultaneously but asynchronously with each other. Each card player shall
write the specified text message to one, common shared resource, a file named 
STACK.txt. When writing to this file, the thread needs to prevent the data from getting 
corrupted by the other card player's threads; to implement this, each card player's 
thread shall use an appropriate IPC mechanism/algorithm.

******************************************* 

Files included in a1 directory:
Source File: a1.c
Header File: a1.h
Makefile
README
Executable: player

*******************************************

Compilation Instructions:

To build and create the "player" executable file, use command
'make' 

Then type player and hit enter
Output is printed to the console and STACK.txt

******************************************* 

Design Decisions:
We initially decided to call threads routine within fopen() and fclose() 
inside the a1.c. But according to problem statement we have to open and close 
STACK.txt inside the critical region in each thread routine, which we have succesfully implemented now.  

******************************************* 

Objectives Learned:

Learned how to implement threads and semaphores.

Learned how to use pthread functions such as pthread_create and pthread_join

Learned how to use semaphore functions such as sem_init, sem_wait, sem_post, sem_destroy
to achieve thread concurrency.
