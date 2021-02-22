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
	bigIntTest02();	



	printf("Buh Bye!\n");
	return EXIT_SUCCESS;
}

//BigInt arithmatic tests;
void static bigIntTest02() {
	int t1, t2;	
  	BigInt *testBi,*testBi1,*testBi2;
	
	testBi1 = createBigInt(4);
	testBi2 = createBigInt(4);
	testBi = NULL;

	t1 = 0xFFFF00FF;  //positive integer
	t2 = 0x00FFFFFE;  //negative integer


	printf("testBi1:  %X, %d\n", t1,t1);
	printf("testBi2:  %X, %d\n", t2,t2);


	//direct assignmnet method as to avoid using initBigInt_int as
	//right now, unsigned int version has not yet been implemented
	*(int *)testBi1->bytes = t1;
	*(int *)testBi2->bytes = t2;


	//for(int i = testBi1->size -1 ; i > -1 ; i--) {
	//	printf("%02X", testBi1->bytes[i] & 0xFF);
	//} printf("\n");
	char t;
	t = 0;
	printf("t: %02X\n", (t-1)&0xFF  );


	printf("addAbsoluteBigInt check:  \n");
	testBi = addAbsoluteBigInt(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	

	printf("subtractAbsoluteBigInt check: \n");
	testBi = subtractAbsoluteBigInt(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");


	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi);
}

//BigInt comparison tests;
void static bigIntTest01() {
	int t1, t2;	
	
	//test cases
	t1 = 0x7AB4D933;  //positive integer
	t2 = 0x7BB4D933;  //positive integer
	//t1 = 0x7AB4D933;  //positive integer
	//t2 = 0xCBB4D933;  //negative integer
	//t1 = 0x7AB4D933;  //positive integer
	//t2 = 0xFFB4D933;  //negative integer
	//t1 = 0xCAB4D933;  //negative integer
	//t2 = 0xCBB4D933;  //negative integer

  	BigInt *testBi,*testBi1,*testBi2;

	printf("%d %d\n", t1, ~t1 + 1);
	printf("%d %d\n", t2, ~t2 + 1);

	testBi1 = createBigInt_int(t1);
	testBi2 = createBigInt_int(t2);

	printf("testBi1:  %X, %d\n", t1,t1);
	printf("testBi2:  %X, %d\n", t2,t2);
	
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
	
	printf("maxValueBigInt check:  ");
	testBi = maxValueBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	
	if(testBi == testBi1) printf("testBi1 is Max \n");
	if(testBi == testBi2) printf("testBi2 is Max \n");

	printf("minValueBigInt check:  ");
	testBi = minValueBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");

	printf("Done with tests, now cleaning up.\n");
	
	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi);
}


