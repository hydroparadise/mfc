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

/*
A
*/
void initBigInt(BigInt *bigInt,int value) {
	bigInt->isNegative = false;
	bigInt->size = value;
	bigInt->bytes = malloc(bigInt->size * sizeof(char));

	//initialize as 0
	for(int i = 0; i < bigInt->size ; i++) {
		bigInt->bytes[i] = 0;
	}
}


/*
Method that converts int to byte array.  Wth most systems, size will be 4
*/
void initBigIntFromInt(BigInt *bigInt,int value) {
	if(value >= 0) bigInt->isNegative = false;
	else bigInt->isNegative = true;

	bigInt->size = sizeof(value);
	bigInt->bytes = malloc(bigInt->size * sizeof(char));

	//converts int into byte array
	for(int i = 0; i < bigInt->size ; i++) {
		bigInt->bytes[i] = (char)(value >> i * 8 & 0xFF);
	}
}




/*
Adds two BigInts, outputs new BigInt
*/
BigInt* addBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	if(bigInt1->isNegative == bigInt2->isNegative) {

		//early check for addition overflow
		char inc;	//used as a +1 for overflow condition
		if(bigInt1->size == bigInt2->size  &&
		   bigInt1->bytes[bigInt1->size] + bigInt2->bytes[bigInt2->size] > 0xFF) 
			inc = 1;
		else inc = 0;

		//setup ou
		output = malloc(sizeof(BigInt));
		initBigInt(output, MAX(bigInt1->size, bigInt2->size) + inc);
		
		
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
