/*
 * SimpleCylinder.h
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef SIMPLECYLINDER_H_
#define SIMPLECYLINDER_H_

#include "GeometryShape.h"

class SimpleCylinder: public GeometryShape {
protected:
	double base , top , height;
	int slices , stacks;
public:
	SimpleCylinder(double, double);
	virtual ~SimpleCylinder();
	double getRadius();
	double getHeight();
	virtual void draw();
};

#endif /* SIMPLECYLINDER_H_ */
