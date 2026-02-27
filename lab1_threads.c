/*
CECS 326 Lab 1 - Threads in C

*/



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* worker_thread(void* arg) {
	(void)arg;

	while (1) {
		sleep(3); //sleep is a cancellation point on POSIX systems
		printf("Worker thread is running...\n");
		fflush(stdout);
	}

	return NULL;
}

int main() {
	pthread_t thread_id;
	// created a new thread
	if (pthread_create(&thread_id, NULL, worker_thread, NULL) != 0) {
		perror("Error creating thread");
		return 1;
	}
	// Give user instructions on what to do
	printf("Press Enter to cancel the worker thread...\n");
	getchar(); //wait for Enter key
	printf("Canceling worker thread...\n");

	if (pthread_cancel(thread_id) !=0) {
		perror("Error canceling thread");
		return 1;
	}

	/* send cancellation request to worker thread
	thread will stop at next cancellation point
	*/

	if (pthread_join(thread_id, NULL) != 0) {
		perror("pthread_join");
		return 1;
	}

	printf("Worker thread canceled successfully.\n");
	printf("Waiting 5 seconds before exiting...\n");

	// wait 5 seconds to show that worker is gone
	sleep(5);

	printf("Main thread eixting.\n");

	return 0;
}
