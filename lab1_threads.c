/*
CECS 326 Lab 1 - Threads in C

*/



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unisted.h>

void* worker_thread(void* arg) {
	(void)arg;

	while (1) {
		sleep(3); //sleep is a cancellation point on POSIX systems
		printf("[worker] I'm alive! (printed every 3 seconds\n");
		fflush(stdout);
	}

	return NULL;
}

int main(void) {
	pthread_t tid;

	if (pthread_create(&tid, NULL, worker_thread, NULL) != 0) {
		perror("pthread_create");
		return 1;
	}
