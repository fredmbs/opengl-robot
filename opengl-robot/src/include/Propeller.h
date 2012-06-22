/*
 * Propeller.h
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef PROPELLER_H_
#define PROPELLER_H_

#include "GeometryShape.h"
#include "Cylinder.h"

class Propeller: public GeometryShape {
private:
	double width, height, deep, frontRadius;
	GLuint vboId;
	double p[6][3];
	double n[4][3];
public:
	Cylinder* front;
	Propeller(double, double, double);
	virtual ~Propeller();
	virtual void draw();
};

#endif /* PROPELLER_H_ */
