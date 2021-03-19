output: main.c
	gcc -mavx512f -pthread main.c

	
clean:
	rm *.o
