/******************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIDs: 823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #3, EMP
Filename: README
******************************************/
CLASS ACCOUNT USED: cssc0843

README contains:
-Assignment #3 Prompt
-Files Included
-Compilation Instructions
-Design Decisions
-Objectives Learned

*******************************************

Prompt:

You shall create a program that uses signals to 
coordinate work among sibling threads. You will 
build one thread to be the countdown timer, one 
thread to be signal catcher/handler, one worker 
thread will work as Wall Clock, and another 
worker thread will work as Alarm.

*******************************************

Files included in a3 directory:
Source File: a3.c
Header File: a3.h
Makefile
README
Executable: emp

*******************************************

Compilation Instructions:

To build and create the "emp" executable file, use command
'make'

Then type emp and hit enter
Interaction with emp will follow

*******************************************

Design Decisions:
- We set up our prompt to print error message if more than 3 arguments
  or less than 3 but more than 1 argument is entered.

- Please do not enter more than 5 arguments as we allocated newargv 
  with just 6 cells where the last cell is a pointer to NULL.

- Earlier we tried to have our main thread work as a signal catcher
  but re-reading problem statement, we decided to create another thread
  that will work as a signal catcher.

- Instead of using signal catcher as handler, we decided to create 
  another function. Both for countdown timer and alarm thread.
- We decided to reuse our parse routine from previous assignment
  a2.c

- We also decided to use a semaphore to avoid race conditions 
  as two of our threads are writing to stdout concurrently. 

*******************************************

Objectives Learned:
- Increased familiarity with signals in C
- Utilising time() to access current system time since 
  UNIX Epoch time.
- Implementing signal handlers and terminating process 
  and its threads using SIGTERM.