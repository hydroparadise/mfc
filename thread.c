#ifndef MFC_THREAD
#define MFC_THREAD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <error.h>

void *entry_point(void *value) {
	printf("Hello from the other thead");
}

void threadTest() {
	pthread_t thread;
	int num = 123;
	pthread_create(&thread, NULL, entry_point, &num);

	pthread_join(thread, NULL);
 
}

#endif


