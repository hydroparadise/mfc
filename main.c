/*


*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <error.h>

#include "mfc.h"


void static bigIntTest01();
void static bigIntTest02();



int main(int argc, char **argv) {
	printf("We gonna have some fun with maths...\n");
	

	

	//bigIntTest01();	
	//bigIntTest02();	
	//bigIntTest03();
	bigIntTest04();

	printf("Buh Bye!\n");
	return EXIT_SUCCESS;
}



