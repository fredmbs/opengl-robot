/*
 * Cylinder.h
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "SimpleCylinder.h"
#include "Disk.h"

class Cylinder: public SimpleCylinder {
protected:
	Disk baseDisk;
	Disk topDisk;
public:
	Cylinder(double radius, double height);
	virtual ~Cylinder();
	virtual void draw();
};

#endif /* CYLINDER_H_ */
