/*
 * Ring.h
 *
 *  Created on: 14/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef RING_H_
#define RING_H_

#include "Cylinder.h"

class Ring: public Cylinder {
protected:
	SimpleCylinder innerCylinder;
public:
	Ring(double, double, double);
	virtual ~Ring();
	double getInnerRadius();
	virtual void draw();
};

#endif /* RING_H_ */
