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
