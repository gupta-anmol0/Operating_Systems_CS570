/******************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIDs: 823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #2, PAM
Filename: README
******************************************/
CLASS ACCOUNT USED: cssc0843

README contains:
-Assignment #2 Prompt
-Files Included
-Compilation Instructions
-Design Decisions
-Objectives Learned

*******************************************

Prompt:
Provide a shell-like interface for launching new programs:
print a prompt "cssc9999% " (where cssc9999 is your username) and 
then wait for the user to type in a file name. Note, PAM will NOT 
have any shell built-in functions (such as cd, setenv, printenv, 
bg, fg, etc), with the exception of pipe and exit.

*******************************************

Files included in a1 directory:
Source File: a2.c
Header File: a2.h
Makefile
README
Executable: pam

*******************************************

Compilation Instructions:

To build and create the "pam" executable file, use command
'make'

Then type pam and hit enter
Interaction with PAM will follow

*******************************************

Design Decisions:
We initially ran into issues with multiple pipe implementation, which took
the majority of our work time to figure out. We also chose to clean up our main function 
by creating multiple functions to streamline the code. 

*******************************************

Objectives Learned:
- Determining how the shell will interact with user input and validation of file names
- Working out how to introduce command line arguments for files 
- Implementing multiple pipes and correctly handling them 