#ifndef MFC_PLOT
#define MFC_PLOT


#include <math.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void gotoxy(int x, int y) {
	printf("%c[%d;%df",0x1B,y,x);
}



void mandelbrotPlot(double xMin, double xMax, double yMin, double yMax) {
	//get window size
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	//plot extents
	double X_MIN = xMin, X_MAX = xMax, Y_MIN = yMin, Y_MAX = yMax;
	
	//
	int MAX_ITERATIONS = 100;
	
	for(int i = 1; i <= w.ws_row - 1; i++) {
		for(int j = 1; j <= w.ws_col; j++) {

			//map pixels i,j to coordinates x,y
			double x,y;
			x = X_MIN + (((double)(j-1)/(double)w.ws_col) * (X_MAX - X_MIN));
			y = Y_MAX - (((double)(i-1)/(double)w.ws_row) * (Y_MAX - Y_MIN));

			int n = 0;
			double zr = x, zi = y;
			
			while(n < MAX_ITERATIONS && zr + zi <  16) {
				double aa = zr * zr - zi * zi;
				double bb = 2.0 * zr * zi;

				zr = aa + x;
				zi = bb + y;
				n++;
			}
			gotoxy(j,i);

			if(n == MAX_ITERATIONS) printf(".");
			else {
				int o = n*9  /  MAX_ITERATIONS;
				printf("%1i", o); 
			} ;
		} 
		//printf("\n");
	}	
}

void mandelbrotCtl() {
	system("clear");
	printf("\e[3J"); //removes repeated screen
	fflush(stdout);
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	double xmin = -2.0, xmax = 1.0, ymin = -1.0, ymax = 1.0, d = 0.1;

	double x = xmax - xmin;
	double y = ymax - ymin;
	double m = 64.0;//zoom factor
	char ch;
	while(ch!='q') {
		

		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		x = xmax - xmin;
		y = ymax - ymin;

		mandelbrotPlot(xmin,xmax,ymin,ymax);
		gotoxy(1,w.ws_row);
		printf("X=%i,Y=%i    xmin=%4f,xmax=%4f,ymin=%4f,ymax=%4f   x=%f,y=%f\0",
			w.ws_col,w.ws_row,xmin,xmax,ymin,ymax,x,y); 

		ch = getch();

		switch(ch) {
			case 'a':
				xmin=xmin-(x/w.ws_col); 
				xmax=xmax-(x/w.ws_col);
				break;
			case 's':
				ymin=ymin-(y/w.ws_row); 
				ymax=ymax-(y/w.ws_row);
				break;
			case 'd':
				xmin=xmin+(x/w.ws_col); 
				xmax=xmax+(x/w.ws_col);
				break;
			case 'w':
				ymin=ymin+(y/w.ws_row); 
				ymax=ymax+(y/w.ws_row);
				break;

			case 'r':
				x=x/m;
				y=y/m;

				xmin=xmin+(x/2.0);
				xmax=xmax-(x/2.0);
				ymin=ymin+(y/2.0);
				ymax=ymax-(y/2.0);
				
				break;
			case 'f':
				
				x=x/m;
				y=y/m;
				
				xmin=xmin-(x/2.0);
				xmax=xmax+(x/2.0);
				ymin=ymin-(y/2.0);
				ymax=ymax+(y/2.0);
				
				break;
		}
	}
	printf("\n");
}


void mandelbrotTest() {
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
		printf("\0");
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
