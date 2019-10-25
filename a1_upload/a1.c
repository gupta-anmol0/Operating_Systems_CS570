
/*****************************************************
Names: Anmol Deep Gupta and Alan Olvera
Usernames: cssc0843 and cssc0842
RedIds:  823381384 and 818313984
Class: CS570 Summer 2019
Assignment: #1, Multiple Thread Management
Filename: a1.c
****************************************************/

#include "a1.h" 																	// all the required header files are in a1.h

/******************************************************* Global Variables **********************************************************************/

static sem_t FLAG;																	// semaphore that will control access to the critical region i.e STACK.txt

FILE *fp;																			// file pointer as a reference to our file

char *arr[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};	// array of char pointers for each thread to display when they run

/*****************************************************************************************************************************************/

												
/*********************************************************** 
Routine for thread 1
Notes: Each thread open STACK.txt and writes in it, prints the appropriate message to the console 
	and exits. As STACK.txt is in critical region in each thread, each thread routine uses semaphore to achieve concurrency.

 ************************************************************/
void* t1(void* arg){	
	static int i;
	for(i = 0; i < 13; i++){
		usleep(125000);																// put to sleep for 125 ms
		sem_wait(&FLAG);															// down(&mutex) before entering critical region

		/* Entering critical section */
		fp = fopen("STACK.txt", "a"); 
		fprintf(fp, "Diamond %s\r\n", arr[i]);										// print the appropriate message to the file
		fprintf(stdout, "Thread 1 is running\n");									// printing the message to the console
		fclose(fp);
		/*Exiting critical section*/

		sem_post(&FLAG);															// up(&mutex) after leaving critical region
	}
}
		/* Routine for thread 2 */

void* t2(void* arg){
	int i;
	for(i = 0; i < 13; i++){
		usleep(250000);
		sem_wait(&FLAG);	

		/* Entering critical section */
		fp = fopen("STACK.txt", "a"); 
		fprintf(fp, "Club %s\r\n",arr[i]);
		fprintf(stdout, "Thread 2 is running\n");
		fclose(fp);
		/*Exiting critical section*/
		sem_post(&FLAG);
	}
}

		/* Routine for thread 3 */
void* t3(void* arg ){
	int i;
	for(i = 0; i < 13; i++){
		usleep(500000);

		sem_wait(&FLAG);	
		/* Entering critical section */
		fp = fopen("STACK.txt", "a"); 
		fprintf(fp, "Heart %s\r\n",arr[i]);
		fprintf(stdout, "Thread 3 is running\n");
		fclose(fp);
		/*Exiting critical section*/
		sem_post(&FLAG);
	}
}
		/* Routine for thread 4 */
void* t4(void* arg){
	int i;
	for(i = 0; i < 13; i++){
		usleep(750000);
		sem_wait(&FLAG);	

		/* Entering critical section */
		fp = fopen("STACK.txt", "a"); 	
		fprintf(fp, "Spade %s\r\n",arr[i]);
		fprintf(stdout, "Thread 4 is running\n");
		fclose(fp);
		/*Exiting critical section*/
		sem_post(&FLAG);
	}
}

int main(){
	
	pid_t mypid;																// to hold the value pid of the calling process
	
	int treturn;																// to check the return value of pthread_create
	pthread_t thread_1, thread_2, thread_3, thread_4;							// creating 4 threads

	if ((fp = fopen("STACK.txt", "w")) == NULL){								// to open file in write mode, creates file if it didn't exist
		fprintf(stderr, "Unable to create file\n");								// return value of fopen is checked and appropriate error message printed 
		exit(2);														
	}

	mypid = getpid();															// getpid() returns the pid of the calling process

	fprintf(fp, "pid = %d\r\n", mypid);											// printing the process's id into the file pointed to by file pointer fp

	fclose(fp);																	// close file

	sem_init(&FLAG, 0, 1);														// initializing the FLAG semaphore

	if ((treturn = pthread_create(&thread_1, NULL, t1, NULL)) != 0){			// checking the return value of pthread_create
		fprintf(stderr, "Exiting process: could not create thread 1\n");		// if not equal to 0, prints an error message and exits
        exit(1);
	}

	if ((treturn = pthread_create(&thread_2, NULL, t2, NULL)) != 0){
		fprintf(stderr, "Exiting process: could not create thread 2\n");
        exit(1);
	}

	if ((treturn = pthread_create(&thread_3, NULL, t3, NULL)) != 0){
		fprintf(stderr, "Exiting process: could not create thread 3\n");
        exit(1);
	}

	if ((treturn = pthread_create(&thread_4, NULL, t4, NULL)) != 0){
		fprintf(stderr, "Exiting process: could not create thread 4\n");
        exit(1);
	}

	pthread_join(thread_1, NULL);												// blocked till the called threads return
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);

	sem_destroy(&FLAG); 														// destroying the semaphore

	
	fprintf(stdout, "Game Over! Respawn ?\n" );										
	
	return 0;
}
