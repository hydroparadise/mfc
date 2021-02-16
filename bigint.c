/*
A big-endian implementation of an arbitrary precision integer
*/

#ifndef BIGINT
#define BIGINT

/*
Basic Strategies
	1) Each time BigInt encounters
*/


typedef struct BigInt {
	int size;
	char *bytes;
	bool isNegative;
} BigInt;

BigInt* addBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subtractBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxSizeBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minSizeBigInt(BigInt *bigInt1, BigInt *bigInt2);


/*
Inits a BigInt with a size parameter where size is the number of bytes
*/
BigInt* createBigInt(int size) {
	BigInt *bigInt;
	bigInt = NULL;	

	if(size > 0) {
		bigInt = malloc(sizeof(BigInt));
		bigInt->isNegative = false;
		bigInt->size = size;
		bigInt->bytes = malloc(size * sizeof(char));

		//initialize as 0
		for(int i = 0; i < bigInt->size ; i++) {
			bigInt->bytes[i] = 0;
		}
	}

	return bigInt;
}


/*
Method initializes a bigint and converts an int to byte array.  Wth most systems, size will be 4
*/
BigInt* createBigInt_int(int value) {
	BigInt *bigInt;	
	bigInt = malloc(sizeof(BigInt));
	if(value >= 0) bigInt->isNegative = false;
	else bigInt->isNegative = true;

	bigInt->size = sizeof(value);
	bigInt->bytes = malloc(bigInt->size * sizeof(char));

	//converts int into byte array
	for(int i = 0; i < bigInt->size ; i++) {
		bigInt->bytes[i] = (char)(value >> i * 8 & 0xFF);
	}
	return bigInt;
}


/*
Returns the larger magnitude of two BinInts
*/
BigInt* maxSizeBigInt(BigInt *bigInt1, BigInt *bigInt2) {

}

/*
Returns the small magnitude of two BinInts
*/
BigInt* minSizeBigInt(BigInt *bigInt1, BigInt *bigInt2) {

}


/*
Adds two BigInts, outputs new BigInt
*/
BigInt* addBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	if(bigInt1->isNegative == bigInt2->isNegative) {

		//early check for addition overflow ty bytes[]
		char inc;	//used as a +1 for overflow condition
		if(bigInt1->bytes[bigInt1->size] > 0 || 
                   bigInt2->bytes[bigInt2->size] > 0) inc = 1;
			
		else inc = 0;

		//setup output BigInt
		output = createBigInt(MAX(bigInt1->size, bigInt2->size) + inc);
		
		int sum, carry;
		for(int i = 0; i < MAX(bigInt1->size, bigInt2->size) ; i++) {
			sum = 0;
			if(i <= bigInt1->size) sum = sum + bigInt1->bytes[i];
			if(i <= bigInt2->size) sum = sum + bigInt2->bytes[i];
			
		}
		
	}
	//else subtractBigInt()

	return output;
}

BigInt* subtractBigInt(BigInt *bigInt1, BigInt *bigInt2) {

}


/*
Clean up big int;
*/
void freeBigInt(BigInt *bigInt) {

	free(bigInt->bytes);
	bigInt = NULL;
	//free(bigInt);	
}

#endif
