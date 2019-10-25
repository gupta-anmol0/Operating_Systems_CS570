/*****************************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIds:  823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #2, PAM
Filename: a2.c
****************************************************/

#include"a2.h"

/*      parameters for parse routine       */

int newargc;
char *newargv[MAXITEMS];
char *token;

/*       parameters for getline            */
char *line = NULL;
size_t linecap = 0;
ssize_t linelen;

/*   parameters for piperoutine   */

int pipe_flag;
int pipe_index[11] = { 0 };				// to store indices for pipes



struct stat sb;							// declaring stat struct for sb  


/********************************   To display the prompt     *************************************/
void display_prompt(){
	printf("cssc0843%% ");
}

/********************** To read the user input and tokenize the words ******************************/
void parse(){
	int i = 1;										// we start storing pipe indices from the second element of the array
	newargc = 0;
	pipe_flag = 0;

	linelen = getline(&line, &linecap, stdin);
	if (linelen == -1 || linelen == 0)
		return;
	token = strtok(line, "\n ");
	while (token != NULL){
		if (strcmp(token, "|") == 0 ){
			pipe_flag++ ;
			newargv[newargc++] = NULL;				// setting the newargv pointer to NULL whenever pipeline occurs
			pipe_index[i++] = newargc;				// storing indices of processes after each occurrence of a pipeline
			token = strtok(NULL, "\n ");			
		}
		else{
			newargv[newargc++] = token; 				// Add tokens into the array
			token = strtok(NULL, "\n ");
		}
	}
	newargv[newargc] = NULL;    
}

/*******************************        Pipe routine      *******************************************/
void piperoutine(){
	int status;
	int pipefd[2 * pipe_flag]; 			
	pid_t grandkid;

	
	for(int i = 0; i < pipe_flag; i++){					
		if ((pipe(pipefd + i * 2)) < 0){
			fprintf(stderr, "Pipe Error\n");
			exit (EXIT_FAILURE);
		}
	}	
	
	

	for (int j = 0, l = 0; j <= pipe_flag; j++){									// we are implementing horizontal pipes 

		fflush(stdout);															// to write all the data stored in respective stream onto the console
		fflush(stderr);															// thus allowing to enter into a new process with a clear buffer

		grandkid = fork();													// i.e one process is created for each executable

		if (0 == grandkid){
			
			if (j != 0){													// if not first child i.e not first executable				
                if(dup2(pipefd[l - 2], STDIN_FILENO) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }               										
			}

			if ( j != pipe_flag){												// if not last child i.e not last executable
				if(dup2(pipefd[l + 1], STDOUT_FILENO) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }				
			}			

			for (int i = 0; i < 2 * pipe_flag; i++)								// close all file descriptors
				close(pipefd[i]);												

			if ((execvp(newargv[pipe_index[j]], newargv + (pipe_index[j]))) < 0){		// execvp to run the executable
				fprintf(stderr, "%s: File not found\n", newargv[pipe_index[j]] );
				exit(4);
			}

		}
		else if(grandkid < 0){
            fprintf(stderr, "Pipe error\n");
            exit(EXIT_FAILURE);
		}	
		l = l + 2;	
	}
	/**************** only the parent gets here and waits for its pipe children to finish**********/
	for (int i = 0; i < 2 * pipe_flag; i++)
		close(pipefd[i]);
	
		
	for (int i = 0; i <= pipe_flag; i++){
    	wait(&status);	          
	}

}

void execute_routine(){

	if (stat(newargv[0], &sb) == 0 && sb.st_mode & S_IXUSR){			
        pid_t kidpid;

        fflush(stdout);
		fflush(stderr);

        if (-1 == (kidpid = fork())){		// FORKING FAILURE
        	perror("Cannot fork");
        	exit(EXIT_FAILURE);
        }
        else if (0 == kidpid){				// CHILD PROCESS	
        	
        	if (pipe_flag != 0)
				piperoutine();
					
        	if( (execvp(newargv[0], newargv)) < 0 ){				// TODO: take in absolute pathname	
				fprintf(stderr, "File not found\n");
				exit(EXIT_FAILURE);
			}					
        }
        else{        			
			for(;;){												// waiting for the child
				pid_t pid;
				pid = wait(NULL);
				if (pid == kidpid){
					break;
				}
			}
					
        	return;
        }
    }

    else{
        printf("Invalid file name\n");
        return;
    }
}

int main(){
	//int j;
	//PATH = getenv("PATH");
	//printf("%s\n", PATH);

	while(1){
		display_prompt();				// display the prompt 
		parse();
	
		if (linelen == 0){
			printf("Please enter a command\n");
			continue;
		}
		else if(linelen == -1){
			fprintf(stderr, "Error occured in reading line or EOF encountered\n" );
			exit(EXIT_FAILURE);
		}
		
		if (strcmp(newargv[0], "exit") == 0){ 		// to exit
			break;	
		}
		if (pipe_flag == 0 && newargc > 2){
			printf("Cannot support more than one arguments\n");
			continue;
		}

		if (newargv[0] != NULL)			
        	execute_routine();
        
        
    }        	
	return 0;

}

