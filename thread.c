#ifndef THREAD
#define THREAD


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


