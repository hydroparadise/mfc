/*


*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "mfc.h"


void static bigIntTest01();



int main(int argc, char **argv) {
	printf("We gonna have some fun with maths...\n");
	

	bigIntTest01();	
	
	return EXIT_SUCCESS;
}

//development testing for BigInt;
void static bigIntTest01() {
  	BigInt *testBi;
	initBigIntFromInt(testBi,0x7AB4D933);
	
	printf("%d\n", 0x7AB4D933);
	printf("%d\n", testBi->size);
	
	//print each each byte as hex pair 
	//for(int i = 0; i < testBi->size ; i++) {
		//      format                     mask
	//	printf("%02X\n", testBi->bytes[i] & 0xFF);
	//}
	
	//print each nibble as decimal
	//for(int i = 0; i < testBi->size ; i++) {
	//	printf("%d\n", testBi->bytes[i] & 0xF);
	//	printf("%d\n", testBi->bytes[i] >> 4 & 0xF);
	//}

	freeBigInt(testBi);
}


