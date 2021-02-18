/*
A big-endian implementation of an arbitrary precision integer
*/

#ifndef MFC_BIGINT
#define MFC_BIGINT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <error.h>


/*
Basic Strategies
	1) Each time BigInt encounters
*/


typedef struct BigInt {
	const int size;
	const bool isNegative;
	char *bytes;

} BigInt;


//TODO: create  header for prototypes
BigInt* createBigInt(int size);
BigInt* createBigInt_int(int value);
BigInt* copyBigInt(BigInt *bigInt);
BigInt* addBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subtractBigInt(BigInt *bigInt1, BigInt *bigInt2);
int compareSizeBigInt(BigInt *bigInt1, BigInt *bigInt2);
int compareValueBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool gtBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool ltBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxSizeBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minSizeBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxValueBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minValueBigInt(BigInt *bigInt1, BigInt *bigInt2);


/*
Inits a BigInt with a size parameter where size is the number of bytes
*/
BigInt* createBigInt(int size) {
	BigInt *output;
	output = NULL;	
	if(size > 0) {
		output = malloc(sizeof(BigInt));
		if(!output)
			error(EXIT_FAILURE, errno, "Could not allocate.");
		
		//this type of assignment is needed to initialize const member
		//of an malloc'd structure
		//cast   dereference
		*(bool *)&output->isNegative = false;
		*(int *)&output->size = size;
		output->bytes = malloc(size * sizeof(char));
		if(output->bytes)
			error(EXIT_FAILURE, errno, "Could not allocate.");

		//initialize as 0
		for(int i = 0; i < output->size ; i++) {
			output->bytes[i] = 0;
		}
	}

	return output;
}


/*
Method creates and initializes a BigInt and converts an int to byte array.  With most systems, size will be 4
*/
BigInt* createBigInt_int(int value) {
	BigInt *output;	
	output = malloc(sizeof(BigInt));
	if(!output)
		error(EXIT_FAILURE, errno, "Could not allocate.");

	if(value >= 0) *(bool *)&output->isNegative = false;
	else *(bool *)&output->isNegative = true;

	*(int *)&output->size = sizeof(value);
	output->bytes = malloc(output->size * sizeof(char));

	//converts int into byte array
	for(int i = 0; i < output->size ; i++) {
		output->bytes[i] = (char)(value >> i * 8 & 0xFF);
	}
	return output;
}


/*
Creates a copy of a BigInt and returns new instance
*/
BigInt* copyBigInt(BigInt *bigInt) {
	BigInt *output;
	output = NULL;
	if(!bigInt && bigInt->size >=0) {
		output = createBigInt(bigInt->size);
		for(int i = 0; i < bigInt->size ; i++) {
			output->bytes[i] = bigInt->bytes[i];
		}
	}
	
	return output;
}


/*
Returns pointer to the larger magnitude of two BinInts
If magnitudes are equal, will return first arg
*/
BigInt* maxMagnitudeBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;
	if(bigInt1 != NULL && bigInt2 != NULL) {
		char val1, val2;
		for(int i = 0 ; i < MAX(bigInt1->size, bigInt2->size); i++) {
			//cant compare directly between 2 BigInts because
			//of possibility of differing sizes
			val1 = 0; val2 = 0;

			//make sure we are within array range to grab value
			if(i < bigInt1->size) {
				//if positive, get value as-is
				if(bigInt1->isNegative == false) val1 = bigInt1->bytes[i];
				//if negative, get 2's compelement
				else val1 = ~bigInt1->bytes[i] + 1;
			}

			//make sure we are within array range to grab value
			if(i < bigInt2->size) {
				//if positive, get value as-is
				if(bigInt2->isNegative == false) val2 = bigInt2->bytes[i];
				//if negative, get 2's compelement
				else val2 = ~bigInt2->bytes[i] + 1;
			}

			if(val1 >= val2) output = bigInt1;
			else output = bigInt2;
		}
		return output;
	}
	else return NULL;
}


/*
Returns the smaller magnitude of two BinInts
If sizes are equal, will return first arg
*/
BigInt* minMagnitudeBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1 == maxMagnitudeBigInt(bigInt1, bigInt2)) return bigInt2;
		else return bigInt1;
	}
	else return NULL;
}


/*
Returns pointer to the larger value of two BinInts
*/
BigInt* maxValueBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1->isNegative == false && bigInt2->isNegative == true) 
			return bigInt1;
		else if(bigInt1->isNegative == true && bigInt2->isNegative == false)
			return bigInt2;
		else if(bigInt1->isNegative == false && bigInt2->isNegative == false)
			return maxMagnitudeBigInt(bigInt1,bigInt2);
		else if(bigInt1->isNegative == true && bigInt2->isNegative == true)
			return minMagnitudeBigInt(bigInt1,bigInt2);
		
	}
	else return NULL;
}


/*
Returns the small magnitude of two BinInts
*/
BigInt* minValueBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1->isNegative == true && bigInt2->isNegative == false) 
			return bigInt1;
		else if(bigInt1->isNegative == false && bigInt2->isNegative == true)
			return bigInt2;
		else if(bigInt1->isNegative == true && bigInt2->isNegative == true)
			return maxMagnitudeBigInt(bigInt1,bigInt2);
		else if(bigInt1->isNegative == false && bigInt2->isNegative == false)
			return minMagnitudeBigInt(bigInt1,bigInt2);
		
	}
	else return NULL;
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
Clean up BigInt
*/
void freeBigInt(BigInt *bigInt) {
	if(bigInt->bytes != NULL) {
		free(bigInt->bytes);
		bigInt->bytes = NULL;
	}

	if(bigInt != NULL) {
		free(bigInt);
		bigInt = NULL;
	}
}

#endif
