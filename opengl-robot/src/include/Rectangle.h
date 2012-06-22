/*
 * Rectangle.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "GeometryShape.h"

namespace GC
{
class Rectangle: public GeometryShape {
protected:
	double width, height, deep;
public:
	Rectangle(double, double, double);
	virtual ~Rectangle();
	virtual void draw();
	inline double getWidth() { return width; };
	inline double getHeight() { return height; };
	inline double getDeep() { return deep; };
};
};
#endif /* RECTANGLE_H_ */
