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
