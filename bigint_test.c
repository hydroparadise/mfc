void bigIntTest05() {
	unsigned int t1,t2,t3;
	BigInt *testBi1, *testBi2;

	testBi1 = newBigInt(1);

	//testBi2 = newBigInt(1);
	//testBi3 = newBigInt(1);

	t1 = 0x1; 
	//t2 = 0xFF;	
	//t3 = 0xFF;

	*(int *)testBi1->chunks = t1;
	//*(int *)testBi2->chunks = t2;
	//*(int *)testBi3->chunks = t3;
	
	for(unsigned int i = 0; i < 1000000; i++) {

		if(i % 10000 == 0)
			printf("%i - %i \n", i, testBi1->size);

		
		//for(int i = testBi1->size -1 ; i > -1 ; i--) {
		//	printf("%08X", testBi1->chunks[i]);
		//} printf("\n");
		
		
		/*
		testBi2 = copyBigInt(testBi1);
		addBigInt(testBi1,testBi2);
		freeBigInt(testBi2);
		*/
		addBigInt(testBi1,testBi1);
	}


	printf("\n");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf("\n");
	printf("Size -> %i\n", testBi1->size);
	
	/*
	printf("\n");
	for(int i = testBi2->size -1 ; i > -1 ; i--) {
		printf("%02X", testBi2->chunks[i] & 0xFF);
	} printf("\n");
	*/
	
	freeBigInt(testBi1);
	//freeBigInt(testBi2);
	//freeBigInt(testBi3);
}


void bigIntTest04() {
	//printf("Size of big int flags: %i\n", sizeof(BigIntFlags));
	//void addMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
	//void subMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
	//void addBigInt(BigInt *bigInt1, BigInt *bigInt2);
	//void subBigInt(BigInt *bigInt1, BigInt *bigInt2);
	unsigned int t1, t2, t3, t4;
	BigInt *testBi1,*testBi2,*testBi3, *testBi4;

	testBi1 = newBigInt(1);
	testBi2 = newBigInt(1);
	testBi3 = newBigInt(1);
	testBi4 = newBigInt(1);

	t1 = 0x000000FF;
	t2 = 0x00FFFFFE;  
	t3 = 0x00000000; 
	t4 = 0xFFFFFFFE; 

	*(int *)testBi1->chunks = t1;
	*(int *)testBi2->chunks = t2;
	*(int *)testBi3->chunks = t3;
	*(int *)testBi4->chunks = t4;


	printf("addMagBigInt check:  ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" + ");
	if(testBi2->isNegative == true) printf("-");
	for(int i = testBi2->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi2->chunks[i]);
	} printf(" = ");
	addMagBigInt(testBi1,testBi2);
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf("\n");

	printf("addMagBigInt check:  ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" + ");
	if(testBi3->isNegative == true) printf("-");
	for(int i = testBi3->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi3->chunks[i]);
	} printf(" = ");
	addMagBigInt(testBi1,testBi3);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf("\n");

	printf("addMagBigInt check:  ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" + ");
	if(testBi4->isNegative == true) printf("-");
	for(int i = testBi4->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi4->chunks[i]);
	} printf(" = ");
	addMagBigInt(testBi1,testBi4);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
		//printf("%02X", testBi1->chunks[i] & 0xFF);
	} printf("\n");

	printf("addBigInt check:  ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" + ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" = ");
	if(testBi1->isNegative == true) printf("-");
	addBigInt(testBi1,testBi1);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf("\n");

	
	printf("subBigInt check:  ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" - ");
	if(testBi4->isNegative == true) printf("-");
	for(int i = testBi4->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi4->chunks[i]);
	} printf(" = ");
	subBigInt(testBi1,testBi4);
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf("\n");

	printf("subBigInt check:  ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi4->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi4->chunks[i]);
	} printf(" - ");
	if(testBi1->isNegative == true) printf("-");
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf(" = ");
	subBigInt(testBi4,testBi1);
	if(testBi4->isNegative == true) printf("-");
	for(int i = testBi4->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi4->chunks[i]);
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

	t1 = 0x00000000000000FFL;
	t2 = 0x0000000000FFFFFEL;  
	t3 = 0x0000000000000000L; 
	t4 = 0x00000000FFFFFFFEL; 

	*(int *)testBi1->chunks = t1;
	*(int *)testBi2->chunks = t2;
	*(int *)testBi3->chunks = t3;
	*(int *)testBi4->chunks = t4;
	
	
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



	//direct assignmnet method as to avoid using initBigInt_int as
	//right now, unsigned int version has not yet been implemented
	//UPDATE: it's now been implemented, but keep as example of
	//using different assigment method
	*(int *)testBi1->chunks = t1;
	*(int *)testBi2->chunks = t2;

	printf("testBi1:  %08X, %u\n", t1,t1);
	for(int i = testBi1->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi1->chunks[i]);
	} printf("\n");

	printf("testBi2:  %08X, %u\n", t2,t2);
	for(int i = testBi2->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi2->chunks[i]);
	} printf("\n");

	//for(int i = testBi1->size -1 ; i > -1 ; i--) {
	//	printf("%02X", testBi1->chunks[i] & 0xFF);
	//} printf("\n");

	printf("addBigInt_new check:  \n");
	testBi = addMagBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i]);
	} printf("\n");
	freeBigInt(testBi);
	
	printf("subMagBigInt_new check: \n");
	testBi = subMagBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i]);
	} printf("\n");
	freeBigInt(testBi);

	printf("addBigInt_new check:  \n");
	testBi = addBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i]);
	} printf("\n");
	freeBigInt(testBi);

	printf("subBigInt_new check:  \n");
	testBi = subBigInt_new(testBi1,testBi2);
	printf("Size: %d\n", testBi->size);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i]);
	} printf("\n");
	freeBigInt(testBi);

	freeBigInt(testBi1);
	freeBigInt(testBi2);
}

//BigInt comparison tests;
void bigIntTest01() {
	int t1, t2;	
	
	//test cases
	t1 = 0x0AB4D933;  //positive integer
	//t2 = 0x7BB4D933;  //positive integer
	//t1 = 0x7AB4D933;  //positive integer
	t2 = 0xCBB4D933;  //negative integer
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

	printf("testBi1:  %08X, %i  size->%u\n", t1,t1,testBi1->size);
	printf("testBi2:  %08X, %i  size->%u\n", t2,t2,testBi2->size);
	printf("testBi3:  %08X, %i  size->%u\n", t1,t1,testBi3->size);
	
	printf("eqMagBigInt check: testBi1, testBi2  %u\n",eqMagBigInt(testBi1, testBi2));
	printf("eqMagBigInt check: testBi1, testBi3  %u\n",eqMagBigInt(testBi1, testBi3));


	printf("maxMagBigInt check:  ");
	testBi = maxMagBigInt(testBi1,testBi2);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i] & 0xFFFFFFFF);
	} printf("\n");

	printf("minMagBigInt check:  ");
	if(testBi->isNegative == true) printf("-");
	testBi = minMagBigInt(testBi1,testBi2);
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i] & UINT_MAX);
	} printf("\n");
	
	printf("maxBigInt check:  ");
	testBi = maxBigInt(testBi1,testBi2);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i] & UINT_MAX);
	} printf("\n");
	
	if(testBi == testBi1) printf("testBi1 is Max \n");
	if(testBi == testBi2) printf("testBi2 is Max \n");

	printf("minBigInt check:  ");
	testBi = minBigInt(testBi1,testBi2);
	if(testBi->isNegative == true) printf("-");
	for(int i = testBi->size -1 ; i > -1 ; i--) {
		printf("%08X", testBi->chunks[i] & UINT_MAX);
	} printf("\n");

	printf("Done with tests, now cleaning up.\n");
	
	freeBigInt(testBi1);
	freeBigInt(testBi2);
	freeBigInt(testBi3);
	freeBigInt(testBi);
}
