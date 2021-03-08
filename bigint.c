/*
A big-endian implementation of an arbitrary precision integer
Magnitude orien
Addition: Augend + Addend = Sum
subion: Minuend - Subtrahend = Difference
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
Analysis:
	Using unsigned int to determine size, the largest value value
	would by 256^(2^32)
	

Basic Strategies Thoughts
1)	Have two dedicated operator slots for all operaters

	
*/




typedef struct BigIntFlags {
	bool isNegative: 1;
	bool isZero: 1;
} BigIntFlags;

typedef struct BigInt {
	unsigned int size;
	bool isNegative;
	//BigIntFlags flags;
	unsigned char *bytes;
} BigInt;


//TODO: create  header for prototypes

//create, destory, resize
BigInt* newBigInt(int size);
BigInt* newBigInt_int(int value);
BigInt* newBigInt_long(long value);
BigInt* copyBigInt_new(BigInt *bigInt);
void freeBigInt(BigInt *bigInt);
void resizeBigInt(BigInt *bigInt, unsigned int newSize);
void autoResizeBigInt(BigInt *bigInt);


//comparsion methods
bool eqMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool eqBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* maxBigInt(BigInt *bigInt1, BigInt *bigInt2);
BigInt* minBigInt(BigInt *bigInt1, BigInt *bigInt2);
bool isZeroBigInt(BigInt *bigInt);

//basic operation
void incMagBigInt(BigInt *bigInt);
void decMagBigInt(BigInt *bigInt);
void incBigInt(BigInt *bigInt);
void decBigInt(BigInt *bigInt);

//mutable operations, first argument gets mutation
void addMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
void subMagBigInt(BigInt *bigInt1, BigInt *bigInt2);
void addBigInt(BigInt *bigInt1, BigInt *bigInt2);
void subBigInt(BigInt *bigInt1, BigInt *bigInt2);


//immutable operations, creates new object
BigInt* addMagBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subMagBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* addBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* subBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* mulBigInt_new(BigInt *bigInt1, BigInt *bigInt2);
BigInt* divBigInt_new(BigInt *bigInt1, BigInt *bigInt2);






/*
Inits a BigInt with a size parameter where size is the number of bytes
*/
BigInt* newBigInt(int size) {
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

		output->bytes = calloc(size, sizeof(char));
		if(!output->bytes)
			error(EXIT_FAILURE, errno, "Could not allocate byte array.");
	}

	return output;
}


/*
Method creates and initializes a BigInt and converts an int to byte array.  
Converts negative ints to two's complement and assigns negative flag to
true.

With most systems, size will be 4
*/
BigInt* newBigInt_int(int value) {
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
	for(unsigned int i = 0; i < output->size ; i++) {
		if (output->isNegative == false)
			output->bytes[i] = (char)(value >> i * 8 & 0xFF);
		else output->bytes[i] = (char)((~value+1) >> i * 8 & 0xFF);
	}
	return output;
}


/*
Method creates and initializes a BigInt and converts an int to byte array.  
Converts negative ints to two's complement and assigns negative flag to
true.

With most systems, size will be 8
*/
BigInt* newBigInt_long(long value) {
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
	for(unsigned int i = 0; i < output->size ; i++) {
		if (output->isNegative == false)
			output->bytes[i] = (char)(value >> i * 8 & 0xFF);
		else output->bytes[i] = (char)((~value+1) >> i * 8 & 0xFF);
	}
	return output;
}

/*
Creates a copy of a BigInt and returns new instance
*/
BigInt* copyBigInt_new(BigInt *bigInt) {
	BigInt *output;
	output = NULL;
	if(bigInt != NULL) {
		output = newBigInt(bigInt->size);
		for(unsigned int i = 0; i < bigInt->size ; i++) {
			output->bytes[i] = bigInt->bytes[i];
		}
	}
	
	return output;
}

/*
Resizes
*/
void resizeBigInt(BigInt *bigInt, unsigned int newSize) {
	if(bigInt != NULL){ 
		
		if(bigInt->size != newSize) {
			int oldSize = bigInt->size;	
			
			bigInt->bytes = realloc(bigInt->bytes, newSize * sizeof(char));
			if(!bigInt->bytes)
				error(EXIT_FAILURE, errno, "Could not rellocate.");
			else bigInt->size = newSize;
			
			//need to initialize new bytes if expanded
			if(newSize > oldSize) {
				for(unsigned int i = newSize - 1; i > newSize - oldSize; i--) {
					bigInt->bytes[i] = 0;
				}
			}
		}	
	}
}

/*

*/
void autoResizeBigInt(BigInt *bigInt) {
	if(bigInt != NULL){ 
		unsigned int newSize = bigInt->size;
		
		while(bigInt->bytes[newSize - 1] == 0 && newSize -1 > 0 ) {
			//printf("byte at %i: %02X\n", newSize - 1, bigInt->bytes[newSize - 1]);
			newSize--;
		}
		//printf("byte at %i: %02X\n", newSize - 1, bigInt->bytes[newSize - 1]);
		//printf("newSize: %i\n", newSize);		
		if(bigInt->size != newSize) {
					
			bigInt->bytes = realloc(bigInt->bytes, newSize * sizeof(char));
			if(!bigInt->bytes)
				error(EXIT_FAILURE, errno, "Could not rellocate.");
			else bigInt->size = newSize;
		}
	}
}

/*
Checks for magnitude equality
Returns false if either argument doesn't pass NULL check
*/
bool eqMagBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		unsigned int i;
		unsigned char val1, val2;		
		i = MAX(bigInt1->size, bigInt2->size) - 1;
		
		do {
			val1 = 0; val2 = 0;
			if(i < bigInt1->size) val1 = bigInt1->bytes[i];
			if(i < bigInt2->size) val2 = bigInt2->bytes[i];

			//printf("i: %i  %02X v %02X -> %i\n", i, val1, val2, val1 == val2);
		} while (i-- > 0 && val1 == val2);
		
		//printf("i: %i  %02X v %02X -> %i\n", i, val1, val2, val1 == val2);
		if(i == -1 && val1 == val2) return true;
		else return false;
	}
	else return false;
}

/*
Checks for equality
Returns false if either argument doesn't pass NULL check
*/
bool eqBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1->isNegative == bigInt2->isNegative)
			return eqMagBigInt(bigInt1, bigInt2);
		else return false;
	}
	return false;
}

/*
Returns pointer to the larger magnitude of two BinInts
If magnitudes are equal, will return first arg
*/
BigInt* maxMagBigInt(BigInt *bigInt1, BigInt *bigInt2) {
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
BigInt* minMagBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	//just use reverse logic based on maxMagBigInt
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1 == maxMagBigInt(bigInt1, bigInt2)) return bigInt2;
		else return bigInt1;
	}
	else return NULL;
}

/*
Returns pointer to the larger value of two BinInts
*/
BigInt* maxBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1->isNegative == false && bigInt2->isNegative == true) 
			return bigInt1;
		else if(bigInt1->isNegative == true && bigInt2->isNegative == false)
			return bigInt2;
		else if(bigInt1->isNegative == false && bigInt2->isNegative == false)
			return maxMagBigInt(bigInt1,bigInt2);
		else if(bigInt1->isNegative == true && bigInt2->isNegative == true)
			return minMagBigInt(bigInt1,bigInt2);
		
	}
	else return NULL;
}


/*
Returns pointer to the smaller value of two BinInts
*/
BigInt* minBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		if(bigInt1->isNegative == true && bigInt2->isNegative == false) 
			return bigInt1;
		else if(bigInt1->isNegative == false && bigInt2->isNegative == true)
			return bigInt2;
		else if(bigInt1->isNegative == true && bigInt2->isNegative == true)
			return maxMagBigInt(bigInt1,bigInt2);
		else if(bigInt1->isNegative == false && bigInt2->isNegative == false)
			return minMagBigInt(bigInt1,bigInt2);
		
	}
	else return NULL;
}


/*
Checks to see if BigInt is 0
Returns false if null
*/
bool isZeroBigInt(BigInt *bigInt) {
	if(bigInt != NULL) {
		unsigned int i = bigInt->size - 1;
		while(i > 0 && bigInt->bytes[i] == 0) {
			i--;
		}
		if(i == 0 && bigInt->bytes[i] == 0)
			return true;
		else return false;
	}
	else return false;
}


/*
Increments BigInt by one
Slightly more efficient than add method
*/
void incMagBigInt(BigInt *bigInt) {
	if(bigInt != NULL) {

		//do carry math if first element is about to overflow
		//otherwise just increment
		if(bigInt->bytes[0] == 0xFF) {
			int i = 0;
			//increase array by 1 if we're at end of array, and about to overflow
			if(i == bigInt->size - 1 &&
				bigInt->bytes[bigInt->size - 1] == 0xFF) {
				bigInt->bytes = realloc(bigInt->bytes, 
					(bigInt->size + 1) * sizeof(char));
				if(!bigInt->bytes)
					error(EXIT_FAILURE, errno, "Could not rellocate.");
				bigInt->size++;
			}

			do {
				bigInt->bytes[i]++;
				i++;
			}
			while(i < bigInt->size - 1 && bigInt->bytes[i] == 0xFF);
			bigInt->bytes[i]++;
		}
		else bigInt->bytes[0]++;
	}
}

/*
Decrements BigInt by one
Slightly more efficient than add method
If value of BigInt is 0, nothing is done because 0 is floor
for a magnitude
Use decBigInt for proper sign handling
*/
void decMagBigInt(BigInt *bigInt){
	if(bigInt != NULL && isZeroBigInt(bigInt) == false) {
		if(bigInt->bytes[0] == 0) {
			int i;
			i = 0;
			do {
				bigInt->bytes[i]--;
				i++;
			}
			while(i < bigInt->size && bigInt->bytes[i] == 0);
			bigInt->bytes[i]--;
		
		}
		else bigInt->bytes[0]--;
	}
}


/*
Sums the magnitude of two BigInts storing the result to first argument.
Expands size as needed (realloc)
*/
void addMagBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		//increase first argument under following conditions
		//1. Addition will cause overflow at last byte
		//2. 2nd arg is larger than 1st
		if(bigInt1->size == bigInt2->size &&  //make sure it's safe to dereference
		   (unsigned short)bigInt1->bytes[bigInt1->size] + 
                   (unsigned short)bigInt2->bytes[bigInt2->size] + 1 > 0xFF)
			resizeBigInt(bigInt1, bigInt1->size +1);
		else {
			BigInt *maxMag = maxMagBigInt(bigInt1, bigInt2);
			if((unsigned short)maxMag->bytes[maxMag->size] + 1 > 0xFF)
				resizeBigInt(bigInt1, bigInt1->size + 1);
			else if (maxMag->size > bigInt1->size)
				resizeBigInt(bigInt1, maxMag->size);
		}
		
		unsigned char val1, val2, carry = 0;
		unsigned short sum;
		for(unsigned int i = 0; i < bigInt1->size; i++) {
			val1 = 0; val2 = 0; sum = 0;
			
			if(i < bigInt1->size) val1 = bigInt1->bytes[i];
			if(i < bigInt2->size) val2 = bigInt2->bytes[i];

			sum = val1 + val2 + carry;
			bigInt1->bytes[i] = sum & 0xFF;

			if(sum > 0xFF) carry = 1;
			else carry = 0;
		}	
	}
}


/*
Subtracts absolute magnitude of two BigInts and assigns to first argument
*/
void subMagBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		//sort out the bigger magnitude needed for proper substitution 
		BigInt *maxMag, *minMag;
		maxMag = maxMagBigInt(bigInt1, bigInt2);
		if(maxMag == bigInt1) minMag = bigInt2;
		else minMag = bigInt1;	

		//if 2nd arg is larger than 1st, risize 1st arg
		if (maxMag->size > bigInt1->size)
			resizeBigInt(bigInt1, maxMag->size);

		unsigned char diff, val2, borrow = 0;
		unsigned short val1;
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

			//printf("(val1&0xFF - borrow) >= val2): %u v %u\n", 
			//	(val1&0xFF - borrow) ,val2 );
			if((val1&0xFF - borrow) >= val2) {
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

			bigInt1->bytes[i] = diff;
		}
	}
}


/*
Sums two BigInts storing the result to first argument.
Expands size as needed (realloc)
*/
void addBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {
		//like signs can add up straight forward
		if(bigInt1->isNegative == bigInt2->isNegative) {
			addMagBigInt(bigInt1, bigInt2);
		}
		else subBigInt(bigInt1, bigInt2);
	}
}


/*
Subtracts two BigInts and assigns to first argument
Expands size as needed (realloc)
*/
void subBigInt(BigInt *bigInt1, BigInt *bigInt2) {
	if(bigInt1 != NULL && bigInt2 != NULL) {	
		BigInt *maxMag, *minMag;
		maxMag = maxMagBigInt(bigInt1, bigInt2);
		if(maxMag == bigInt1) minMag = bigInt2;
		else minMag = bigInt1;	

		if(bigInt1->isNegative == bigInt2->isNegative) {
			subMagBigInt(bigInt1, bigInt2);
			if(maxMag == bigInt1) bigInt1->isNegative = maxMag->isNegative;
			else bigInt1->isNegative ^= maxMag->isNegative;
		} 
		else {
			addMagBigInt(bigInt1, bigInt2);
			bigInt1->isNegative = maxMag->isNegative; 
		}		
	}
}


/*
Returns new object as sum of two BigInts magnitudes
*/
BigInt* addMagBigInt_new(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		output = newBigInt(MAX(bigInt1->size, bigInt2->size) + 1);
		unsigned char val1, val2, carry = 0;
		unsigned short sum;
		carry = 0;
		for(unsigned int i = 0 ; i < MAX(bigInt1->size, bigInt2->size); i++) {
			//cant compare directly between 2 BigInts because
			//of possibility of differing sizes
			val1 = 0; val2 = 0; sum = 0;
			
			if(i < bigInt1->size) val1 = bigInt1->bytes[i];
			if(i < bigInt2->size) val2 = bigInt2->bytes[i];

			sum = val1 + val2 + carry;
			output->bytes[i] = sum & 0xFF;

			if(sum > 0xFF) carry = 1;
			else carry = 0;

			//printf("i: %d, Val1: %u, Val2 %u, Sum: %u, Sum2: %u, Carry: %u\n", 
			//	i, val1&0xFF, val2&0xFF, sum, sum2,  carry);


		}
		output->bytes[MAX(bigInt1->size, bigInt2->size)] = carry;
		output->isNegative = bigInt1->isNegative;
	}
}



/*
Subtracts absolute values of two BigInts
*/
BigInt* subMagBigInt_new(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		output = newBigInt(MAX(bigInt1->size, bigInt2->size));

		//sort out the bigger magnitude needed for proper substitution 
		BigInt *maxMag, *minMag;
		maxMag = maxMagBigInt(bigInt1, bigInt2);
		if(maxMag == bigInt1) minMag = bigInt2;
		else minMag = bigInt1;	

		unsigned char diff, val2, borrow = 0;
		unsigned short val1;	
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

			//printf("(val1&0xFF - borrow) >= val2): %u v %u\n", 
			//	(val1&0xFF - borrow) ,val2 );
			if((val1&0xFF - borrow) >= val2) {
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
BigInt* addBigInt_new(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		//like signs can add up straight forward
		if(bigInt1->isNegative == bigInt2->isNegative) {
			output = addMagBigInt_new(bigInt1, bigInt2);
			output->isNegative = bigInt1->isNegative;
		}
		else output = subBigInt_new(bigInt1, bigInt2);
	}
	return output;
}


/*
subs 2nd argument from the first argument
*/
BigInt* subBigInt_new(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;
	
	if(bigInt1 != NULL && bigInt2 != NULL) {	
		BigInt *maxMag, *minMag;
		maxMag = maxMagBigInt(bigInt1, bigInt2);
		if(maxMag == bigInt1) minMag = bigInt2;
		else minMag = bigInt1;	

		if(bigInt1->isNegative == bigInt2->isNegative) {
			output = subMagBigInt_new(bigInt1, bigInt2);
			if(maxMag == bigInt1) output->isNegative = maxMag->isNegative;
			else output->isNegative ^= maxMag->isNegative;
		} 
		else {
			output = addMagBigInt_new(bigInt1, bigInt2);
			output->isNegative = maxMag->isNegative; 
		}		
	}

	return output;
}


BigInt* mulBigInt_new(BigInt *bigInt1, BigInt *bigInt2) {
	BigInt *output;
	output = NULL;

	if(bigInt1 != NULL && bigInt2 != NULL) {
		output = NULL;
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
