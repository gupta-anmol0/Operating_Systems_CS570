/******************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIDs: 823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #3, Event Management Program
Filename: a3.c
******************************************/



#include "a3.h"

static sem_t FLAG;														//semaphore that will control access to the critical region i.e stdout

/**********      parameters for parse routine       ****************/

int newargc;
char *newargv[MAXITEMS];
char *token;

/* ***************      parameters for getline     *****************/
char *line;
size_t linecap = 0;
ssize_t linelen;


/*****************************   	Display of the prompt  	   ****************************/

void display_prompt(){
	printf("%% emp: ");
}

/*************************************** Parse Routine ***************************************/
void parse(){
	newargc = 0;

	linelen = getline(&line, &linecap, stdin);
	
	
	if (linelen == -1 || linelen == 0 || linelen == 1)
		return;
	
	
	token = strtok(line, "\n ");

	while (token != NULL){	
		newargv[newargc++] = token; 											// Add tokens into the array
		token = strtok(NULL, "\n ");	
	}
	
	newargv[newargc] = NULL; 													// terminating the array with a NULL

}

/*************** Catching the SIGUSR1 signal to terminate all threads and the process *************/

void term_handler(int sig){		

	pid_t pid = getpid();	
	/******* entering critical region ********/
	sem_wait(&FLAG);
	printf("This indicates the termination of the process and all threads\n");
	sem_post(&FLAG);
	/******* entering critical region ********/
	kill(pid, SIGTERM);

}

/*************** Catching the SIGUSR2 signal to print an ALARM messag to the stdout  *************/

void alarm_handler(int sig){
	/******* entering critical region ********/

	sem_wait(&FLAG);												// access to the stdout file is considered as critical region
	fprintf(stdout, "This is your ALARM SIGNAL\n");					// because in this program 2 threads are writing to the terminal
	sem_post(&FLAG);												// and this can lead to race conditions

	/******* exiting critical region ********/
}

/*************************************** Thread Routine **************************************/

/***************** Countdown Timer ******************/

void* t1(void* countdown){											 

	int i;															// to check value returned by sleep function
	pid_t pid = getpid();
	int count = atoi(countdown);
	if ((i = sleep(count)) > 0)
		exit(EXIT_FAILURE);	
	kill(pid, SIGUSR1);												// sending user defined signal 1 to self
	pthread_exit(0);
}

/***************** Signal Handler ******************/

void* t2(void* arg){											
	(void) signal(SIGUSR1, term_handler);							// invokes call to user-defined term_handler to deal with SIGUSR1
	(void) signal(SIGUSR2, alarm_handler);							// invokes call to user-defines alarm_handler to deal with SIGUSR2
	pthread_exit(0);
}

/***************** Wall Clock ******************/

void* t3(void* arg){													
	time_t current_time;
    char* c_time_string;
	for(;;){
		if(atoi(arg) == 1)
			sleep(1);
		else if (atoi(arg) == 60)
			sleep(60);
		else {
			fprintf(stderr, "Only values of 1 or 60 is allowed as second argument\n" );
			exit(EXIT_FAILURE);
		}
		current_time = time(NULL);
		c_time_string = ctime(&current_time);

		/******* entering critical region ********/
		sem_wait(&FLAG);
		fprintf(stdout, "Current time is %s", c_time_string);						// here stdout file is the shared resources between two threads
		sem_post(&FLAG);
		/******* exiting critical region ********/
	}
}

/***************** Alarm ******************/
void* t4(void* arg){											
	int i;
	int alarm = atoi(arg);
	pid_t pid = getpid();

	if ((i = sleep(alarm)) > 0)
		exit(EXIT_FAILURE);
	
	kill(pid, SIGUSR2);																// sending user defined signal 2 to the self
	pthread_exit(0);
}
/********************************* Main function ****************************************/
int main(){												

	int treturn;																// to check the return value of pthread_create
	pthread_t thread_1, thread_2, thread_3, thread_4;							// pthread_t is a special data type to represent threads

	sem_init(&FLAG, 0, 1);														// initializing the FLAG semaphore

	while (1){

		display_prompt();														 // for displaying the prompt 

		parse();																// parse routine is used for parsing the command line arguments

		if (linelen == 1){														// deafult values when no argument is entered
			newargv[0] = "32";
			newargv[1] = "1";
			newargv[2] = "17";																	
			newargv[3] = NULL;
			
		}

		else if(linelen == -1){
			fprintf(stderr, "Error occured in reading line or EOF encountered\n" );
			exit(EXIT_FAILURE);
		}

		if (strcmp(newargv[0], "exit") == 0){ 									// to exit
			break;	
		}

		if (newargc > 3){
			printf("Only three argument are allowed\n");
			continue;
		}

		else if (newargc > 0 && newargc < 3){
			printf("Please input at least 3 arguments or none\n");
			continue;
		}

		if (strcmp(newargv[0], "exit") == 0){ 									// to exit
			break;	
		}		

		/*  creating the countdown timer thread */
		if ((treturn = pthread_create(&thread_1, NULL, t1, newargv[0])) != 0){			// checking the return value of pthread_create
			fprintf(stderr, "Exiting process: could not create thread 1\n");			// if not equal to 0, prints an error message and exits
        	exit(1);
		}
		
		/*  creating the signal handler thread */
		if ((treturn = pthread_create(&thread_2, NULL, t2, NULL)) != 0){
			fprintf(stderr, "Exiting process: could not create thread 2\n");
        	exit(1);
		}
		
		/*  creating the wall clock thread */
		if ((treturn = pthread_create(&thread_3, NULL, t3, newargv[1])) != 0){
			fprintf(stderr, "Exiting process: could not create thread 3\n");
        	exit(1);
		}
		
		/*  creating the alarm thread */
		if ((treturn = pthread_create(&thread_4, NULL, t4, newargv[2])) != 0){
			fprintf(stderr, "Exiting process: could not create thread 4\n");
        	exit(1);
		}	
		
		pthread_join(thread_1, NULL);												// blocked till the called threads return
		pthread_join(thread_2, NULL);
		pthread_join(thread_3, NULL);
		pthread_join(thread_4, NULL);			
	}
	return 0;
}
