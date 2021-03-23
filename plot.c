#ifndef MFC_PLOT
#define MFC_PLOT


#include <math.h>
#include <sys/ioctl.h>


void mandelrbotTest() {
	//get window size
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	//plot extents
	double X_MIN = -2.0, X_MAX = 1.0, Y_MIN = - 1.0, Y_MAX = 1.0;
	
	//
	int MAX_ITERATIONS = 50;
	
	for(int i = 1; i <= w.ws_row; i++) {
		for(int j = 1; j <= w.ws_col; j++) {

			//map pixels i,j to coordinates x,y
			double x,y;
			x = X_MIN + (((double)(j-1)/(double)w.ws_col) * (X_MAX - X_MIN));
			y = Y_MAX - (((double)(i-1)/(double)w.ws_row) * (Y_MAX - Y_MIN));

			//printf("i = %2i, j = %2i\n", i, j); 
			//printf("x = %4f, y = %4f\n", x, y); 

			int n = 0;
			double zr = x, zi = y;
			
			while(n < MAX_ITERATIONS && zr + zi <  16) {
				double aa = zr * zr - zi * zi;
				double bb = 2.0 * zr * zi;
				
				zr = aa + x;
				zi = bb + y;
				
				//printf("zr = %4f, zi = %4f\n", zr, zi);
				n++;
			}
			//printf("n %i\n", n);
			 
			if(n == MAX_ITERATIONS) printf(".");
			else {
				int o = n*9  /  MAX_ITERATIONS;
				printf("%1i", o );
			} ;
		} 
		printf("\n");
	}
	
}

void fillScreenTest() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	for(int i = 0; i < w.ws_row - 1; i++){
		for(int k = 0; k < w.ws_col - 1; k++) {
			printf("x");
		} 
		printf("\n");
	}
}	


void winSizeTest() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	printf("lines: %d\n", w.ws_row);
	printf("columns: %d\n", w.ws_col);
}



#endif
