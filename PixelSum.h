/*
 * PixelSum.h
 *
 *  Created on: Jan 19, 2019
 *      Author: Sriram
 */

#ifndef PIXELSUM_H_
#define PIXELSUM_H_
#include "common.h"

class PixelSum {
private:
	unsigned char* image;
	int Width;
	int Height;
	int *integralImage;
	int *nonZeroCountIntegralImage;
	void computeIntegralImagesThread(int Index, bool directionCheck);
public:
	PixelSum(const unsigned char* buffer, int xWidth, int xHeight);
	PixelSum(const PixelSum&);
	PixelSum();
	virtual ~PixelSum();
	PixelSum& operator= (const PixelSum&);
	unsigned int getPixelSum(int x0, int y0, int x1, int y1) const;
	double getPixelAverage(int x0, int y0, int x1, int y1) const;
	int getNonZeroCount(int x0, int y0, int x1, int y1) const;
	double getNonZeroAverage(int x0, int y0, int x1, int y1) const;
	void computeIntegralImages();
	void computeIntegralImages2();
	void computeIntegralImages3();

};

#endif /* PIXELSUM_H_ */
