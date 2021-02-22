/*
A big-endian implementation of an arbitrary precision integer
Magnitude orien
Addition: Augend + Addend = Sum
Subtraction: Minuend - Subtrahend = Difference
Multiplication: Multiplicand x Multiplier = Product
Division: Dividend / Divisor = Quotient
Modulation: Dividend % Divisor = Remainder
Exponentiation: Base ^ Exponent = Power
Nth Root:  Degree V Radicand = Root
Logarithm: log base (antilogarithm) = logarithm




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


//typedef struct BigInt {
//	const int size;
//	const bool isNegative;
//	char *bytes;
//} BigInt;

typedef struct BigInt {
	int size;
	bool isNegative;
	char *bytes;
} BigInt;


//TODO: create  header for prototypes
BigInt* createBigInt(int size);
BigInt* createBigInt_int(int value);
BigInt* copyBigInt(BigInt *bigInt);
int compareSizeBigInt(BigInt *bigInt1, BigInt *bigInt2);
int compareValueBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool gtBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool ltBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxMagnitudeBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minMagnitudeBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxValueBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minValueBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* addBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subtractBigInt(BigInt *bigInt1, BigInt *bigInt2);

/*
Inits a BigInt with a size parameter where size is the number of bytes
*/
BigInt* createBigInt(int size) {
	BigInt *output;
	output = NULL;	
	if(size > 0) {
		output = malloc(sizeof(BigInt));
		if(!output)
			error(EXIT_FAILURE, errno, "Could not allocate struct.");
		
		//this type of assignment is needed to initialize const struct member
		//of an malloc'd structure
		//cast   dereference
		//*(bool *)&output->isNegative = false;
		//*(int *)&output->size = size;
		output->isNegative = false;
		output->size = size;

		output->bytes = malloc(size * sizeof(char));
		if(!output->bytes)
			error(EXIT_FAILURE, errno, "Could not allocate byte array.");

		//initialize as 0
		for(int i = 0; i < output->size ; i++) {
			output->bytes[i] = 0;
		}
	}

	return output;
}


/*
Method creates and initializes a BigInt and converts an int to byte array.  
Converts negative ints to two's complement and assigns negative flag to
true.

With most systems, size will be 4
*/
BigInt* createBigInt_int(int value) {
	BigInt *output;	
	output = malloc(sizeof(BigInt));
	if(!output)
		error(EXIT_FAILURE, errno, "Could not allocate.");
	
	//this type of assignment is needed to initialize a const struct member
	//if(value >= 0) *(bool *) &output->isNegative = false;
	//else *(bool *)&output->isNegative = true;
	if(value >= 0) output->isNegative = false;
	else output->isNegative = true;	


	*(int *)&output->size = sizeof(value);
	output->bytes = malloc(output->size * sizeof(char));
	if(!output->bytes)
		error(EXIT_FAILURE, errno, "Could not allocate.");

	//converts int into byte array
	//if negative number, convert two's complement
	for(int i = 0; i < output->size ; i++) {
		if (output->isNegative == false)
			output->bytes[i] = (char)(value >> i * 8 & 0xFF);
		else output->bytes[i] = (char)((~value+1) >> i * 8 & 0xFF);
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
		unsigned char val1, val2;
		for(int i = 0 ; i < MAX(bigInt1->size, bigInt2->size); i++) {
			//cant compare directly between 2 BigInts because
			//of possibility of differing sizes
			val1 = 0; val2 = 0;
			
			//arg 1
			//make sure we are within array range to grab value
			if(i < bigInt1->size) val1 = bigInt1->bytes[i];

			//arg 2
			//make sure we are within array range to grab value
			if(i < bigInt2->size) val2 = bigInt2->bytes[i];

			if(val1 >= val2) {
				output = bigInt1;
				//printf("maxMag %d: bigInt1 %02X v %02X \n", i, val1&0xFF, val2&0xFF);
			}
			else {
				output = bigInt2;
				///printf("maxMag %d: bigInt2 %02X v %02X \n", i, val1&0xFF, val2&0xFF);
			}
		}
	}
	return output;
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


BigInt* addAbsoluteBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		output = createBigInt(MAX(bigInt1->size, bigInt2->size) + 1);
		unsigned char val1, val2, carry;
		unsigned short sum;
		carry = 0;
		for(int i = 0 ; i < MAX(bigInt1->size, bigInt2->size); i++) {
			//cant compare directly between 2 BigInts because
			//of possibility of differing sizes
			val1 = 0; val2 = 0; sum = 0;
			
			if(i < bigInt1->size) val1 = bigInt1->bytes[i];
			if(i < bigInt2->size) val2 = bigInt2->bytes[i];

			sum = val1 + val2 + carry;
			
			if(sum > 0xFF) {
				carry = (sum >> 8) & 0xFF;
				sum = sum & 0xFF;
			}
			else carry = 0;

			//printf("i: %d, Val1: %u, Val2 %u, Sum: %u, Sum2: %u, Carry: %u\n", 
			//	i, val1&0xFF, val2&0xFF, sum, sum2,  carry);

			output->bytes[i] = sum;
		}
		output->bytes[MAX(bigInt1->size, bigInt2->size)] = carry;
		output->isNegative = bigInt1->isNegative;
	}
}

BigInt* subtractAbsoluteBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		output = createBigInt(MAX(bigInt1->size, bigInt2->size));
		unsigned char diff, val2, borrow;
		unsigned short val1;

		//sort out the bigger magnitude needed for proper subtraction 
		BigInt *maxMag, *minMag;

		maxMag = maxMagnitudeBigInt(bigInt1, bigInt2);
		if(maxMag == bigInt1) minMag = bigInt2;
		else minMag = bigInt1;	

		borrow = 0;	
		for(int i = 0 ; i < MAX(maxMag->size, minMag->size); i++) {
			//cant compare directly between 2 BigInts because
			//of possibility of differing sizes
			val1 = 0; val2 = 0; diff = 0;
			
			//arg 1
			//make sure we are within array range to grab value
			if(i < maxMag->size) val1 = maxMag->bytes[i];

			//arg 2
			//make sure we are within array range to grab value
			if(i < minMag->size) val2 = minMag->bytes[i];

			//printf("(val1&0xFF - borrow) >= val2): %u v %u\n", (val1&0xFF - borrow) ,val2 );
			if((val1&0xFF - borrow) >= val2) {
				printf("a");
				diff = (val1 - borrow) - val2;
				borrow = 0;
			}
			else {  
				//borrowing time
				//if val2 > val2, then it assumed that there is something
				//that can be borrowed at maxMag->bytes[i + 1]
				diff = ((val1&0xFF + 0x100) - borrow)  - val2;

				borrow = 1;
			}
			//printf("i: %d, val1: %u,    val2 %u,   diff: %u, borrow: %u\n", 
			//	i,     val1&0xFF, val2&0xFF, diff&0xFF,     borrow);

			output->bytes[i] = diff;
		}
	}

	return output;
}

/*
Adds two BigInts, outputs new BigInt
*/
BigInt* addBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		//like signs can add up straight forward
		if(bigInt1->isNegative == bigInt2->isNegative) {
			output = addAbsoluteBigInt(bigInt1, bigInt2);
			output->isNegative = bigInt1->isNegative;
		}
		else output = subtractBigInt(bigInt1, bigInt2);
	}
	return output;
}


BigInt* subtractBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;
	
	if(bigInt1 != NULL && bigInt2 != NULL) {	

		if(bigInt1->isNegative == bigInt2->isNegative) {
			
			
		} 
		else {
			
			output = addAbsoluteBigInt(bigInt1, bigInt2);
			
		}		


		
	}

	return output;
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
