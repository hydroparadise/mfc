	int n = 1;
	// little endian if true
	if(*(char *)&n == 1) {
	
		//12 = 0x0C -> (int) 0x0C,0x00,0x00,0x00

	
		printf("Little Endian\n");
	}
	else {
		
	}


	printf("%d\n", a);
	printf("%d\n", ~a);

	printf("%d\n", b);
	printf("%d\n", ~b);
	
	printf("%d\n", (a + ~b) + 1);
	printf("%d\n", (b + ~a) + 1);




	//print each byte as hex pair 
	for(int i = 0; i < testBi->size ; i++) {
		//      format                     mask
		printf("%02X\n", testBi->bytes[i] & 0xFF);
	}
	
	//print each nibble as decimal
	for(int i = 0; i < testBi->size ; i++) {
		printf("%d\n", testBi->bytes[i] & 0xF);
		printf("%d\n", testBi->bytes[i] >> 4 & 0xF);
	}




				
		//if(bigInt1->isNegative == bigInt2->isNegative) {
			unsigned int val1, val2, sum, sum2, carry;

			output = createBigInt(MAX(bigInt1->size, bigInt2->size) + 1);
			for(int i = 0 ; i < MAX(bigInt1->size, bigInt2->size); i++) {
				//cant compare directly between 2 BigInts because
				//of possibility of differing sizes
				val1 = 0; val2 = 0; sum = 0; sum2 = 0;
				
				//if(i < bigInt1->size) val1 = bigInt1->bytes[i];
				//if(i < bigInt2->size) val2 = bigInt2->bytes[i];

				if(i < bigInt1->size) {
					//if positive, get value as-is
					//if(bigInt1->isNegative == false) val1 = bigInt1->bytes[i];
					//if negative, get 2's compelement
					//else val1 = ~bigInt1->bytes[i] + 1;

					val1 = bigInt1->bytes[i];
				}

				//arg 2
				//make sure we are within array range to grab value
				if(i < bigInt2->size) {
					//if positive, get value as-is
					//if(bigInt2->isNegative == false) val2 = bigInt2->bytes[i];
					//if negative, get 2's compelement
					//else val2 = ~bigInt2->bytes[i] + 1;

					val2 = bigInt2->bytes[i];
				}

				sum = val1&0xFF + val2&0xFF + carry&0xFF;
				
				if(sum > 0xFF) {
					carry = (sum >> 8) & 0xFF;
					sum2 = sum & 0xFF;
				}
				else carry = 0;

				printf("Val1: %u, Val2 %u, Sum: %u, Sum2: %u, Carry: %u\n", 
					val1&0xFF, val2&0xFF, sum, sum2,  carry);

				output->bytes[i] = sum;
			}
			output->bytes[output->size] = carry;


