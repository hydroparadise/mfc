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



int main(int argc, char **argv) {
	printf("We gonna have some fun with maths...\n");
	

	bigIntTest01();	
	
	return EXIT_SUCCESS;
}

//development testing for BigInt;
void static bigIntTest01() {
	int t1, t2;	
	t1 = 0x7AB4D933;
	t2 = 0x7BB4D933;

  	BigInt *testBi,*testBi1,*testBi2;

	testBi1 = createBigInt_int(t1);
	testBi2 = createBigInt_int(t2);

	printf("testBi1:  %X\n", t1);
	printf("testBi2:  %X\n", t2);
	
	printf("maxMagnitudeBigInt check:  ");
	testBi = maxMagnitudeBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");

	printf("minMagnitudeBigInt check:  ");
	testBi = minMagnitudeBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	

	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi);
}


