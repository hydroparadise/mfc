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


//works for console, but code will need to be factored to make work else where
void mandelbrotPlot(long double xMin, long double xMax, long double yMin, long double yMax) {
	//get window size
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	
	//max number of iterations per pixel
	int const MAX_ITERATIONS = 100;
	int const CONVERGE_BOUNDARY = 16;
	
	//iterate x and y on screen map to plot coordinates
	for(int i = 1; i <= w.ws_row - 1; i++) {	// y
		for(int j = 1; j <= w.ws_col; j++) {	//x

			//map pixels i,j to coordinates x,y
			long double x,y;
			x = xMin + (((long double)(j-1)/(long double)w.ws_col)*(xMax-xMin));
			y = yMax - (((long double)(i-1)/(long double)w.ws_row)*(yMax-yMin));

			int n = 0;		//iterations
			double zr = x, zi = y;	//zr = real, zi = imaginary
			
			//iteratate until hit max iterations or function diverges
			while(n < MAX_ITERATIONS && zr + zi <  CONVERGE_BOUNDARY) {
				long double aa = zr * zr - zi * zi;
				long double bb = 2.0 * zr * zi;
				zr = aa + x;
				zi = bb + y;
				n++;
			}
			//set cursor
			gotoxy(j,i);

			//plot point
			//prints '.' if in Mandelbrot set
			if(n == MAX_ITERATIONS) printf(".");
			else {
				//if not in Mandelbrot, prints char 0-9 based on iterations
				int o = n*9/MAX_ITERATIONS;
				printf("%1i", o); 
			} ;
		} 
	}	
}

//allows to pan and zoom Madelblot Plot
void mandelbrotCtl() {
	system("clear"); //clears screen
	printf("\e[3J"); //removes repeated screen
	fflush(stdout);  //flushes stdout buffer
	
	//inint struct, and ask system for console row and col size
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	//set initial coodinates for mandelbrot plot
	long double xmin = -2.0, xmax = 1.0, ymin = -1.0, ymax = 1.0;
	
	//get x and y width to reset bounds of window
	long double x = 0;
	long double y = 0;

	//the higher the number, the slower the zoom
	long double m = 64.0;//zoom factor
	char ch;
	
	
	while(ch!='q') {//quit and break loop
		
		//get number of characters x and y on console screen
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);

		//update x,y based on previous action
		x = xmax - xmin;
		y = ymax - ymin;
		
		mandelbrotPlot(xmin,xmax,ymin,ymax);
		gotoxy(1,w.ws_row);

		//show plot coordinates
		printf("X=%i,Y=%i    xmin=%4Lf,xmax=%4Lf,ymin=%4Lf,ymax=%4Lf   x=%4Lf,y=%4Lf \0",
			w.ws_col,w.ws_row, xmin, xmax, ymin, ymax, x, y); 
		
		//stops, and grabs single character and moves a long
		//does not require return key like getchar();
		ch = getch();

		switch(ch) {
			case 'a': //pan left
				xmin=xmin-(x/w.ws_col); 
				xmax=xmax-(x/w.ws_col);
				break;
			case 's': //pan right
				ymin=ymin-(y/w.ws_row); 
				ymax=ymax-(y/w.ws_row);
				break;
			case 'd': //pan down
				xmin=xmin+(x/w.ws_col); 
				xmax=xmax+(x/w.ws_col);
				break;
			case 'w': //pan up
				ymin=ymin+(y/w.ws_row); 
				ymax=ymax+(y/w.ws_row);
				break;

			case 'r': //zoom in

				//TODO: guard against complete precision loss
				//window gets stuck once presision is lost
				x=x/m;
				y=y/m;
				xmin=xmin+(x/2.0);
				xmax=xmax-(x/2.0);
				ymin=ymin+(y/2.0);
				ymax=ymax-(y/2.0);
				break;
			case 'f': //zoom out
				
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
