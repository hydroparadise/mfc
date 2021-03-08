

void bigIntTest04() {
	//printf("Size of big int flags: %i\n", sizeof(BigIntFlags));
	//void addMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
	//void subMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
	//void addBigInt(BigInt *bigInt1, BigInt *bigInt2);
	//void subBigInt(BigInt *bigInt1, BigInt *bigInt2);

	BigInt *bigInt;
	bigInt = newBigInt(1);

	BigInt *testBi1,*testBi2,*testBi3, *testBi4;

	testBi1 = newBigInt_int(100);
	testBi2 = newBigInt_int(243434);
	testBi3 = newBigInt_int(0);
	testBi4 = newBigInt_int(-34);


	printf("addBigInt_new check:  \n");
	addMagBigInt(testBi1,testBi2);
	printf("Size: %d\n", testBi1->size);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi1->bytes[i] & 0xFF);
	} printf("\n");

	addMagBigInt(testBi1,testBi3);
	printf("Size: %d\n", testBi1->size);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi1->bytes[i] & 0xFF);
	} printf("\n");

	addMagBigInt(testBi1,testBi4);
	printf("Size: %d\n", testBi1->size);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi1->bytes[i] & 0xFF);
	} printf("\n");

	addMagBigInt(testBi1,testBi1);
	printf("Size: %d\n", testBi1->size);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi1->bytes[i] & 0xFF);
	} printf("\n");

	addBigInt(testBi1,testBi4);
	printf("Size: %d\n", testBi1->size);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi1->bytes[i] & 0xFF);
	} printf("\n");


	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi3);
	freeBigInt(testBi4);

	//bigInt->flags.isZero = true;
	//bigInt->flags->isNegative = false;
	
}


/*
Resizing test
*/
void bigIntTest03() {
	int t1, t2, t3, t4;
	BigInt *testBi1,*testBi2,*testBi3, *testBi4;

	testBi1 = newBigInt(4);
	testBi2 = newBigInt(4);
	testBi3 = newBigInt(4);
	testBi4 = newBigInt(4);

	t1 = 0x000000FF;
	t2 = 0x00FFFFFE;  
	t3 = 0x00000000; 
	t4 = 0xFFFFFFFE; 
	

	*(int *)testBi1->bytes = t1;
	*(int *)testBi2->bytes = t2;
	*(int *)testBi3->bytes = t3;
	*(int *)testBi4->bytes = t4;
	
	
	printf("testBi1:  %X, %u\n", t1,t1);
	printf("t1 Before: %i\n", testBi1->size);
	autoResizeBigInt(testBi1);
	printf("t1 After:  %i\n", testBi1->size);

	printf("testBi2:  %X, %u\n", t2,t2);
	printf("t2 Before: %i\n", testBi2->size);
	autoResizeBigInt(testBi2);
	printf("t2 After:  %i\n", testBi2->size);

	printf("testBi3:  %X, %u\n", t3,t3);
	printf("t3 Before: %i\n", testBi3->size);
	autoResizeBigInt(testBi3);
	printf("t3 After:  %i\n", testBi3->size);

	printf("testBi4:  %X, %u\n", t4,t4);
	printf("t4 Before: %i\n", testBi4->size);
	autoResizeBigInt(testBi4);
	printf("t4 After:  %i\n", testBi4->size);

	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi3);
	freeBigInt(testBi4);
}

//BigInt arithmatic tests;
void bigIntTest02() {
	int t1, t2;	
  	BigInt *testBi,*testBi1,*testBi2;
	
	testBi1 = newBigInt(4);
	testBi2 = newBigInt(4);
	testBi = NULL;

	t1 = 0xFFFF00FF;  //positive integer
	t2 = 0x00FFFFFE;  //negative integer

	printf("testBi1:  %X, %u\n", t1,t1);
	printf("testBi2:  %X, %u\n", t2,t2);

	//direct assignmnet method as to avoid using initBigInt_int as
	//right now, unsigned int version has not yet been implemented
	//UPDATE: it's now been implemented, but keep as example of
	//using different assigment method
	*(int *)testBi1->bytes = t1;
	*(int *)testBi2->bytes = t2;

	//for(int i = testBi1->size -1 ; i > -1 ; i--) {
	//	printf("%02X", testBi1->bytes[i] & 0xFF);
	//} printf("\n");

	printf("addBigInt_new check:  \n");
	testBi = addMagBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	freeBigInt(testBi);
	
	printf("subMagBigInt_new check: \n");
	testBi = subMagBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	freeBigInt(testBi);

	printf("addBigInt_new check:  \n");
	testBi = addBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	freeBigInt(testBi);

	printf("subBigInt_new check:  \n");
	testBi = subBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	freeBigInt(testBi);

	freeBigInt(testBi1);
	freeBigInt(testBi2);
}

//BigInt comparison tests;
void bigIntTest01() {
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

  	BigInt *testBi,*testBi1,*testBi2, *testBi3;

	printf("%d %d\n", t1, ~t1 + 1);
	printf("%d %d\n", t2, ~t2 + 1);

	testBi1 = newBigInt_int(t1);
	testBi2 = newBigInt_int(t2);
	testBi3 = newBigInt_int(t1);

	printf("testBi1:  %X, %i\n", t1,t1);
	printf("testBi2:  %X, %i\n", t2,t2);
	printf("testBi3:  %X, %i\n", t1,t1);
	
	printf("maxMagBigInt check: testBi1, testBi2  %u\n",eqMagBigInt(testBi1, testBi2));
	printf("maxMagBigInt check: testBi1, testBi3  %u\n",eqMagBigInt(testBi1, testBi3));


	printf("maxMagBigInt check:  ");
	testBi = maxMagBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");

	printf("minMagBigInt check:  ");
	testBi = minMagBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	
	printf("maxBigInt check:  ");
	testBi = maxBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");
	
	if(testBi == testBi1) printf("testBi1 is Max \n");
	if(testBi == testBi2) printf("testBi2 is Max \n");

	printf("minBigInt check:  ");
	testBi = minBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi->bytes[i] & 0xFF);
	} printf("\n");

	printf("Done with tests, now cleaning up.\n");
	
	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi3);
	freeBigInt(testBi);
}
