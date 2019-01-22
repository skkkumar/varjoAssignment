/*
 * main.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: root
 */


#include "PixelSum.h"


int main(int argc, char **argv) {

unsigned char buffer[100] = {
		0,0,0,0,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,0,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2};

PixelSum PixelObj(buffer,10,10);
int x0 = 9;
int y0 = 9;
int x1 = 10;
int y1 = 10;


cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<flush;

return 0;
}


