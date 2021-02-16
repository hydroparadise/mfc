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
	printf("a\n");
  	BigInt *testBi,*testBi1,*testBi2;
	testBi1 = createBigInt_int(0x7AB4D933);
	testBi2 = createBigInt_int(0x7BB4D933);
	
	testBi = maxMagnitudeBigInt(testBi1,testBi2);
	//testBi = testBi2;

	//printf("%d\n", 0x7AB4D933);
	printf("%d\n", testBi->size);

	//print each byte as hex pair 
	for(int i = 0; i < testBi->size ; i++) {
		//      format                     mask
		printf("%02X\n", testBi->bytes[i] & 0xFF);
	}
	
	//print each nibble as decimal
	for(int i = 0; i < testBi->size ; i++) {
		//printf("%d\n", testBi->bytes[i] & 0xF);
		//printf("%d\n", testBi->bytes[i] >> 4 & 0xF);
	}

	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi);
}


