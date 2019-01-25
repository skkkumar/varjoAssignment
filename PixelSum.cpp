/*
 * PixelSum.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Sriram
 */

#include "PixelSum.h"

//Constructors
PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int xHeight) {
//	initialize
	image = const_cast<unsigned char*>(buffer);
	Width = xWidth;
	Height = xHeight;
//	allocate memory for integralImage and nonZeroCountIntegralImage
	integralImage = new int[Width * Height];
	nonZeroCountIntegralImage = new int[Width * Height];
//	Compute Integral image / pixel sums
	computeIntegralImages2(); // there are 3 Different implementation available. The difference is the execution time.
}

PixelSum::PixelSum(const PixelSum& Input) {
//	Initialize from another object
	image = Input.image;
	Width = Input.Width;
	Height = Input.Height;
	integralImage = Input.integralImage;
	nonZeroCountIntegralImage = Input.nonZeroCountIntegralImage;
}

PixelSum::PixelSum() {
//	Default initialize it as 0
	image = 0;
	Width = 0;
	Height = 0;
	integralImage = 0;
	nonZeroCountIntegralImage = 0;
}

PixelSum::~PixelSum() {
	// TODO Auto-generated destructor stub
}

// equal to operator
PixelSum& PixelSum::operator=(const PixelSum& ImageIP) {
	PixelSum ImageOP(ImageIP.image, ImageIP.Width, ImageIP.Height);
	return ImageOP;
}

// An alternate way to calculate the Integral image. Alternate to computeIntegralImages.
void PixelSum::computeIntegralImages2() {
	//for all rows
	for (int integralRow = 0; integralRow < Height; integralRow++) {
		unsigned int localSum = 0;
		unsigned int localnonZeroPixelCount = 0;
		//for all cols
		for (int integralCol = 0; integralCol < Width; integralCol++) {
			// compute cumulative sum for each row.
			localSum += *(image + integralRow * Width + integralCol);
			//if the pixel is not zero, increment the non-zero counter
			if (*(image + integralRow * Width + integralCol) != 0) {
				localnonZeroPixelCount++;
			}
			//ignoring the first zero
			if (integralRow > 0) {
				// take the pixel above the current pixel location
				*(integralImage + integralRow * Width + integralCol) =
						*(integralImage + (integralRow - 1) * Width
								+ integralCol);

				*(nonZeroCountIntegralImage + integralRow * Width + integralCol) =
						*(nonZeroCountIntegralImage + (integralRow - 1) * Width
								+ integralCol);
			}

			// add cumulative sum to the integral image
			*(integralImage + integralRow * Width + integralCol) += localSum;
			*(nonZeroCountIntegralImage + integralRow * Width + integralCol) +=
					localnonZeroPixelCount;
//			cout << *(integralImage + integralRow * Width + integralCol) << ", "
//					<< flush;
		}
//		cout << endl << flush;
	}
	return;
}

// Implementation for calculating integral image using multi-threading
void PixelSum::computeIntegralImagesThread(int Index, bool directionCheck) {
	//for all rows
	if (!directionCheck) { // First iteration code
		//for all cols
		for (int integralCol = 0; integralCol < Width; integralCol++) {
//			Compute cumulative sum along Rows for specific Index rows
			*(integralImage + Index * Width + integralCol) += *(image
					+ Index * Width + integralCol);
			if (integralCol > 0)
				*(integralImage + Index * Width + integralCol) +=
						*(integralImage + Index * Width + integralCol - 1);
			if (*(image + Index * Width + integralCol) != 0) {
				*(nonZeroCountIntegralImage + Index * Width + integralCol) += 1;
			}
			if (integralCol > 0) {
				*(nonZeroCountIntegralImage + Index * Width + integralCol) +=
						*(nonZeroCountIntegralImage + Index * Width
								+ integralCol - 1);
			}
		}

	} else {  // second iteration code. for all columns
		//for all rows
		for (int integralRow = 0; integralRow < Height; integralRow++) {
//			Compute cumulative sum along columns for specific Index columns
			if (integralRow > 0)
				*(integralImage + integralRow * Width + Index) +=
						*(integralImage + (integralRow - 1) * Width + Index);

			if (integralRow > 0) {
				*(nonZeroCountIntegralImage + integralRow * Width + Index) +=
						*(nonZeroCountIntegralImage + (integralRow - 1) * Width
								+ Index);
			}
		}

	}

	return;
}

// Rough implementation of computing integral images, which can be rewritten to run with multiple threads in parallel
void PixelSum::computeIntegralImages3() {

//Compute cumulative sum, first half of integral image along Rows.
	for (int integralRow = 0; integralRow < Height; integralRow++) {
		computeIntegralImagesThread(integralRow, false);
	}

////for all rows
//	for (int integralRow = 0; integralRow < Height; integralRow++) {
//		//for all cols
//		for (int integralCol = 0; integralCol < Width; integralCol++) {
//
//			cout
//					<< *(nonZeroCountIntegralImage + integralRow * Width
//							+ integralCol) << ", " << flush;
//		}
//		cout << endl << flush;
//	}
//	cout << "**************************" << endl << flush;

//Compute cumulative sum, Second half of integral image along Columns.
	for (int integralCol = 0; integralCol < Width; integralCol++) {
		computeIntegralImagesThread(integralCol, true);
	}

//	for (int integralRow = 0; integralRow < Height; integralRow++) {
//		//for all cols
//		for (int integralCol = 0; integralCol < Width; integralCol++) {
//
//			cout
//					<< *(nonZeroCountIntegralImage + integralRow * Width
//							+ integralCol) << ", " << flush;
//		}
//		cout << endl << flush;
//	}
}

// Another alternate way to compute the integral image.
void PixelSum::computeIntegralImages() {

	//for all rows
	for (int integralRow = 0; integralRow < Height; integralRow++) {
		//for all cols
		for (int integralCol = 0; integralCol < Width; integralCol++) {

//			II(x,y) = I(x,y)
			*(integralImage + integralRow * Width + integralCol) = *(image
					+ integralRow * Width + integralCol);
			//if the pixel is not zero, increment the non-zero counter
			if (*(image + integralRow * Width + integralCol) != 0) {
				*(nonZeroCountIntegralImage + integralRow * Width + integralCol) =
						1;
			}

//			II(x,y) += II(x,y-1)
			//ignoring the first row as row-1 is zero
			if (integralRow > 0) {
				*(integralImage + integralRow * Width + integralCol) +=
						*(integralImage + (integralRow - 1) * Width
								+ integralCol);
				*(nonZeroCountIntegralImage + integralRow * Width + integralCol) +=
						*(nonZeroCountIntegralImage + (integralRow - 1) * Width
								+ integralCol);
			}
//			II(x,y) += II(x-1,y)
			//ignoring the first column as column-1 is zero
			if (integralCol > 0) {
				*(integralImage + integralRow * Width + integralCol) +=
						*(integralImage + integralRow * Width
								+ (integralCol - 1));
				*(nonZeroCountIntegralImage + integralRow * Width + integralCol) +=
						*(nonZeroCountIntegralImage + integralRow * Width
								+ (integralCol - 1));
			}

//			II(x,y) -= II(x-1,y-1)
//			Ignore the first row and first column as II(x-1,y-1) in these area will be zero
			if (integralCol > 0 && integralRow > 0) {
				*(integralImage + integralRow * Width + integralCol) -=
						*(integralImage + (integralRow - 1) * Width
								+ (integralCol - 1));
				*(nonZeroCountIntegralImage + integralRow * Width + integralCol) -=
						*(nonZeroCountIntegralImage + (integralRow - 1) * Width
								+ (integralCol - 1));
			}
//			cout
//					<< *(nonZeroCountIntegralImage + integralRow * Width
//							+ integralCol) << ", " << flush;
		}
//		cout << endl << flush;
	}
	return;
}

//Get sum of pixel in a given search window
unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const {
	// Window limit correction.
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

//	If the search window is outside the search space
	if (!((x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			|| (x1 > 0 && x1 < Width && y1 > 0 && y1 < Height)))
		return 0;

//	If the search area is partial inside the image crop it to the boundary
	x0 = (x0 > 0 ? x0 - 1 : 0);
	y0 = (y0 > 0 ? y0 - 1 : 0);
	x1 = (x1 < Width ? x1 : Width - 1);
	y1 = (y1 < Height ? y1 : Height - 1);

//	If the window is a single pixel after all the above checks
	if (x0 == x1 && y0 == y1) {
//		Boundary condition check
		if (x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			return (*(image + y0 * Width + x0));
		else
			return 0;
	}

//	Take the 4 corners of the window
	int a = *(integralImage + y0 * Width + x0);
	int b = *(integralImage + y0 * Width + x1);
	int c = *(integralImage + y1 * Width + x1);
	int d = *(integralImage + y1 * Width + x0);
//	compute the sum from pixelsum
	unsigned int sum = c - b - d + a;
	return sum;
}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const {
//	Get the sum of the given window
	unsigned int sum = getPixelSum(x0, y0, x1, y1);
	// Window limit correction.
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

	//	If the search window is outside the search space
	if (!((x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			|| (x1 > 0 && x1 < Width && y1 > 0 && y1 < Height)))
		return 0;
	//	If the search area is partial inside the image crop it to the boundary
	x0 = (x0 > 0 ? x0 - 1 : 0);
	y0 = (y0 > 0 ? y0 - 1 : 0);
	x1 = (x1 < Width ? x1 : Width - 1);
	y1 = (y1 < Height ? y1 : Height - 1);

	// prepare denominator
	double denominator = 0;
	if (x0 == x1 || y0 == y1) { // for single pixel condition
		if (x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			denominator = 1;
		else
			return 0;
	} else
		denominator = (double) ((abs(x1 - x0) + 1) * (abs(y1 - y0) + 1)); // Get the number of pixels in a given window
	if (sum == 0 && denominator == 0) // Avoiding infinity
		return 0;
	double average = (double) sum / denominator; // get the average/mean
	return average;
}

int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const {
	// Window limit correction.
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
	//	If the search window is outside the search space
	if (!((x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			|| (x1 > 0 && x1 < Width && y1 > 0 && y1 < Height)))
		return 0;
	//	If the search area is partial inside the image crop it to the boundary
	x0 = (x0 > 0 ? x0 - 1 : 0);
	y0 = (y0 > 0 ? y0 - 1 : 0);
	x1 = (x1 < Width ? x1 : Width - 1);
	y1 = (y1 < Height ? y1 : Height - 1);

	//	If the window is a single pixel after all the above checks
	if (x0 == x1 && y0 == y1) {
		//	Boundary condition check
		if (x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			return 1;
		else
			return 0;
	}

//	Take the 4 corners of the window
	int a = *(nonZeroCountIntegralImage + y0 * Width + x0);
	int b = *(nonZeroCountIntegralImage + y0 * Width + x1);
	int c = *(nonZeroCountIntegralImage + y1 * Width + x1);
	int d = *(nonZeroCountIntegralImage + y1 * Width + x0);
//	compute the sum from pixelsum
	unsigned int sum = c - b - d + a;
	return sum;
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const {
	// Window limit correction.
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

	//	If the search window is outside the search space
	if (!((x0 > 0 && x0 < Width && y0 > 0 && y0 < Height)
			|| (x1 > 0 && x1 < Width && y1 > 0 && y1 < Height)))
		return 0;

	//	If the search area is partial inside the image crop it to the boundary
	x0 = (x0 > 0 ? x0 - 1 : 0);
	y0 = (y0 > 0 ? y0 - 1 : 0);
	x1 = (x1 < Width ? x1 : Width - 1);
	y1 = (y1 < Height ? y1 : Height - 1);

//	Get the number of non-zero pixel count
	int nonZeroCount = getNonZeroCount(x0, y0, x1, y1);
//	Get the sum of pixel in the given window
	int sum = getPixelSum(x0, y0, x1, y1);

	if (nonZeroCount == 0 && sum == 0) // Avoiding infinity
		return 0;
	double average = (double) sum / (double) nonZeroCount; // get the average/mean with non-zero pixel count
	return average;
}
