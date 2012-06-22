/*
 * Cage.h
 *
 *  Created on: 17/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef CAGE_H_
#define CAGE_H_

#include "Shape.h"

class CubicCage: public Shape {
private:
	double quadSize, startPos;
	int numQuads;
public:
	CubicCage(double, double);
	virtual ~CubicCage();
	virtual void draw();
};

#endif /* CAGE_H_ */
