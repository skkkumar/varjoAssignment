/*
 * main.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Sriram
 */


#include "PixelSum.h"


int main(int argc, char **argv) {
//Data buffer
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

// Initialize with the image and dimensions as 10x10
PixelSum PixelObj(buffer,10,10);

// Case 1
int x0 = 1;
int y0 = 1;
int x1 = 3;
int y1 = 3;

cout << "Case 1 : Between (1,1) and (3,3)" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 2
x0 = 9;
y0 = 9;
x1 = 1;
y1 = 1;

cout << "Case 2 : Between (9,9) and (1,1) - Reversed the points of case 1" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 3
x0 = 1;
y0 = 1;
x1 = 1;
y1 = 1;

cout << "Case 3 : Between (1,1) and (1,1) - Single pixel" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 4
x0 = 9;
y0 = 9;
x1 = 11;
y1 = 13;

cout << "Case 4 : Between (9,9) and (11,13) - Boundary condition, where there is only one pixel in the search window and remaining are outside the window" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 5
x0 = 23;
y0 = 19;
x1 = 11;
y1 = 13;

cout << "Case 5 : Between (23,19) and (11,13) - Window completely outside the search window" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 6
x0 = -23;
y0 = -19;
x1 = -11;
y1 = -13;

cout << "Case 6 : Between (-23,-19) and (-11,-13) - Window completely outside the search window in a different space" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 7
x0 = -23;
y0 = -19;
x1 = 1;
y1 = 3;

cout << "Case 7 : Between (-23,-19) and (1,3) - The window is at the bottom half with few pixels inside the image." << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 8
x0 = 1;
y0 = 9;
x1 = 1;
y1 = 3;

cout << "Case 8 : Between (1,9) and (1,3) - Window with same column and different rows" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;


// Case 9
x0 = 4;
y0 = 4;
x1 = 6;
y1 = 6;

cout << "Case 9 : Between (4,4) and (6,6) - Check the non-zero element count in the 3x3 matrix there is one non-zero element. So total element count is 8." << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 10
x0 = 2;
y0 = 3;
x1 = 0;
y1 = 0;

cout << "Case 10 : Between (2,3) and (0,0) - Check the non-zero element count " << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;

// Case 11
x0 = 2;
y0 = 3;
x1 = 6;
y1 = 3;

cout << "Case 11 : Between (2,3) and (6,3) - Window with same row and different column" << endl<<flush;
cout << "Sum = " << PixelObj.getPixelSum(x0,y0,x1,y1)<<endl<<flush;
cout << "Average = " <<  PixelObj.getPixelAverage(x0,y0,x1,y1)<<endl<<flush;

cout << "NonZero Count = " << PixelObj.getNonZeroCount(x0,y0,x1,y1)<<endl<<flush;
cout << "NonZero Average = " << PixelObj.getNonZeroAverage(x0,y0,x1,y1)<<endl<<endl<<flush;


return 0;
}





