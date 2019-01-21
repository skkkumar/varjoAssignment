/*
 * PixelSum.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: root
 */

#include "PixelSum.h"

PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int xHeight) {
	image = const_cast<unsigned char*>(buffer);
	Width = xWidth;
	Height = xHeight;
	integralImage = new int[Width * Height];
	nonZeroIntegralImage = new int[Width * Height];
	computeIntegralImages();
}
PixelSum::PixelSum(const PixelSum& Input) {
	image = Input.image;
	Width = Input.Width;
	Height = Input.Height;
	integralImage = Input.integralImage;
	nonZeroIntegralImage = Input.nonZeroIntegralImage;
}

PixelSum::PixelSum() {
	image = 0;
	Width = 0;
	Height = 0;
	integralImage = 0;
	nonZeroIntegralImage = 0;
}

PixelSum::~PixelSum() {
	// TODO Auto-generated destructor stub
}

//void imgResizeBuffer(Image *src, int width, int height)
//{
//	src->xWidth = width;
//	src->xHeight = height;
//	memset(src->buffer,0,sizeof(float)*src->xWidth*src->xHeight);
//}

//PixelSum& PixelSum::operator=(const PixelSum& ImageIP) {
//	PixelSum ImageOP(ImageIP.ImageBuff.buffer,ImageIP.ImageBuff.xWidth,ImageIP.ImageBuff.xHeight);
////	ImageOP.ImageBuff.buffer = ImageIP.ImageBuff.buffer;
////	ImageOP.ImageBuff.xHeight = ImageIP.ImageBuff.xHeight;
////	ImageOP.ImageBuff.xWidth = ImageIP.ImageBuff.xWidth;
//	return ImageOP;
//}



void PixelSum::computeIntegralImages() {
	for (int Integralrow = 0; Integralrow < Height; Integralrow++) {
		for (int Integralcol = 0; Integralcol < Width; Integralcol++) {
			unsigned int sum = 0;
			unsigned int nonZeroPixelCount = 0;
			for (int row = 0; row < Integralrow; row++)
				for (int col = 0; col < Integralcol; col++){
					sum += *(image + row * Width + col);
					if (*(image + row * Width + col) != 0)
					{
						nonZeroPixelCount++;
					}
				}
			*(integralImage + Integralrow * Width + Integralcol) = (int) sum;
			*(nonZeroIntegralImage + Integralrow * Width + Integralcol) = (int) nonZeroPixelCount;
			cout << *(integralImage + Integralrow * Width + Integralcol) << ", " << flush;
		}
		cout << endl << flush;
	}
	return;
}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const {
	if (x0 > x1) {
		int temp = x0;
		x0 = x1;
		x1 = temp;
	}

	if (y0 > y1) {
		int temp = y0;
		y0 = y1;
		y1 = temp;
	}
	int a = *(integralImage + y0 * Width + x0);
	int b = *(integralImage + y0 * Width + x1);
	int c = *(integralImage + y1 * Width + x1);
	int d = *(integralImage + y1 * Width + x0);
	unsigned int sum = c - b - d + a;
	return sum;
}
double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const {
	unsigned int sum = getPixelSum(x0, y0, x1, y1);
	double average = sum / ((x1 - x0) * (y1 - y0));
	return average;
}

int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const {
	if (x0 > x1) {
		int temp = x0;
		x0 = x1;
		x1 = temp;
	}

	if (y0 > y1) {
		int temp = y0;
		y0 = y1;
		y1 = temp;
	}
	int a = *(nonZeroIntegralImage + y0 * Width + x0);
	int b = *(nonZeroIntegralImage + y0 * Width + x1);
	int c = *(nonZeroIntegralImage + y1 * Width + x1);
	int d = *(nonZeroIntegralImage + y1 * Width + x0);
	unsigned int sum = c - b - d + a;
	return sum;
}
double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const {
	int sum = getNonZeroCount(x0, y0, x1, y1);
	double average = sum / ((x1 - x0) * (y1 - y0));
	return average;
}
//
//int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const {
// return 0;
//}
//double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const {
// return 0;
//}
