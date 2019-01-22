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

PixelSum& PixelSum::operator=(const PixelSum& ImageIP) {
	PixelSum ImageOP(ImageIP.image, ImageIP.Width, ImageIP.Height);
	return ImageOP;
}

void PixelSum::computeIntegralImages() {
	for (int Integralrow = 0; Integralrow < Height; Integralrow++) {
		for (int Integralcol = 0; Integralcol < Width; Integralcol++) {
			unsigned int sum = 0;
			unsigned int nonZeroPixelCount = 0;
			for (int row = 0; row <= Integralrow; row++)
				for (int col = 0; col <= Integralcol; col++) {
					sum += *(image + row * Width + col);
					if (*(image + row * Width + col) != 0) {
						nonZeroPixelCount++;
					}
				}
			*(integralImage + Integralrow * Width + Integralcol) = (int) sum;
			*(nonZeroIntegralImage + Integralrow * Width + Integralcol) =
					(int) nonZeroPixelCount;
			cout << *(integralImage + Integralrow * Width + Integralcol) << ", "
					<< flush;
		}
		cout << endl << flush;
	}
	return;
}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const {
	if (!(x0 > 0 && x0 < Width && y0 > 0 && y0 < Height && x1 > 0 && x1 < Width
			&& y1 > 0 && y1 < Height))
		return 0;

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
	x0 = (x0 > 0 ? x0 : 0);
	y0 = (y0 > 0 ? y0 : 0);
	x1 = (x1 < Width ? x1 : Width - 1);
	y1 = (y1 < Height ? y1 : Height - 1);
	if (x0 == x1 && y0 == y1) {
		if (x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			return (*(image + y0 * Width + x0));
		else
			return 0;
	}

	int a = *(integralImage + y0 * Width + x0);
	int b = *(integralImage + y0 * Width + x1);
	int c = *(integralImage + y1 * Width + x1);
	int d = *(integralImage + y1 * Width + x0);
	unsigned int sum = c - b - d + a;
	return sum;
}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const {
	if (!(x0 > 0 && x0 < Width && y0 > 0 && y0 < Height && x1 > 0 && x1 < Width
			&& y1 > 0 && y1 < Height))
		return 0;
	unsigned int sum = getPixelSum(x0, y0, x1, y1);

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
	double denominator = 0;
	if (x0 == x1 || y0 == y1) {
		if (x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			denominator = 1;
		else
			return 0;
	} else
		denominator = (double) ((abs(x1 - x0) + 1) * (abs(y1 - y0) + 1));
	if (sum == 0 && denominator == 0)
		return 0;
	double average = (double) sum / denominator;
	return average;
}

int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const {
	if (!(x0 > 0 && x0 < Width && y0 > 0 && y0 < Height && x1 > 0 && x1 < Width
			&& y1 > 0 && y1 < Height))
		return 0;

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
	x0 = (x0 > 0 ? x0 : 0);
	y0 = (y0 > 0 ? y0 : 0);
	x1 = (x1 < Width ? x1 : Width - 1);
	y1 = (y1 < Height ? y1 : Height - 1);
	if (x0 == x1 && y0 == y1) {
		if (x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			return 1;
		else
			return 0;
	}

	int a = *(nonZeroIntegralImage + y0 * Width + x0);
	int b = *(nonZeroIntegralImage + y0 * Width + x1);
	int c = *(nonZeroIntegralImage + (y1 < Height ? y1 : Height - 1) * Width
			+ (x1 < Width ? x1 : Width - 1));
	int d = *(nonZeroIntegralImage + (y1 < Height ? y1 : Height - 1) * Width
			+ (x0 > 0 ? x0 : 0));

	cout << a << " " << b << " " << c << " " << d << endl << flush;
	unsigned int sum = c - b - d + a;
	return sum;
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const {
	if (!(x0 > 0 && x0 < Width && y0 > 0 && y0 < Height && x1 > 0 && x1 < Width
			&& y1 > 0 && y1 < Height))
		return 0;
	int nonZeroCount = getNonZeroCount(x0, y0, x1, y1);
	int sum = getPixelSum(x0, y0, x1, y1);
	if (nonZeroCount == 0 && sum == 0)
		return 0;
	double average = (double) sum / (double) nonZeroCount;
	return average;
}
