/*
 * main.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: root
 */


#include "PixelSum.h"


int main(int argc, char **argv) {

unsigned char buffer[100] = {0,0,0,0,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2,
		1,2,3,43,5,78,4,2,43,2};

PixelSum PixelObj(buffer,10,10);

cout << "Sum = " << PixelObj.getPixelSum(0,0,1,2)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(0,0,1,2)<<endl<<flush;

cout << "NonZero = " << PixelObj.getNonZeroCount(0,0,1,2)<<endl<<flush;
cout << "NonZero Average = " <<  PixelObj.getPixelAverage(0,0,1,2)<<endl<<flush;

return 0;
}


