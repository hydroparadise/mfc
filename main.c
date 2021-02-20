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

	return EXIT_SUCCESS;
}

//BigInt arithmatic tests;
void static bigIntTest02() {
  	BigInt *testBi,*testBi1,*testBi2;
	
	testBi1 = createBigInt(4);
	testBi2 = createBigInt(4);
	testBi = NULL;

	*(int *)testBi1->bytes = 0xFFFFFFFF;
	*(int *)testBi2->bytes = 0xFFFFFFFF;

	//for(int i = testBi1->size -1 ; i > -1 ; i--) {
	//	printf("%02X", testBi1->bytes[i] & 0xFF);
	//} printf("\n");
	
	testBi = addBigInt(testBi1,testBi2);	

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
	//t1 = 0x7AB4D933;  //positive integer
	//t2 = 0x7BB4D933;  //positive integer
	//t1 = 0x7AB4D933;  //positive integer
	//t2 = 0xCBB4D933;  //negative integer
	t1 = 0xCAB4D933;  //negative integer
	t2 = 0xCBB4D933;  //negative integer

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
	
	printf("minValueBigInt check:  ");
	testBi = minValueBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");

	printf("addBigInt check:  ");
	testBi = addBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");


	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi);
}


