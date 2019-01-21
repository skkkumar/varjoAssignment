/*
 * PixelSum.h
 *
 *  Created on: Jan 17, 2019
 *      Author: root
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
	int *nonZeroIntegralImage;
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
};

#endif /* PIXELSUM_H_ */
