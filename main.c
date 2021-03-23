/*


*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <error.h>
#include <limits.h>
#include <immintrin.h>


#include "mfc.h"



int main(int argc, char **argv) {
	printf("We gonna have some fun with maths...\n");
	__m256 t;

	printf("%lu\n",ULONG_MAX);

	bigIntTest01();	
	bigIntTest02();	
	bigIntTest03();
	bigIntTest04();
	bigIntTest05();

	printf("Buh Bye!\n");
	return EXIT_SUCCESS;
}



