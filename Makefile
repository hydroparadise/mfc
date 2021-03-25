output: main.c
	gcc -mavx512f -pthread -lncurses -ltinfo -lm main.c

	
clean:
	rm *.o
