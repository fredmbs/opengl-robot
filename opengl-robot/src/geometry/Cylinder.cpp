/*
 * Cylinder.cpp
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#include "Cylinder.h"

Cylinder::Cylinder(double radius, double height)
	:SimpleCylinder(radius, height),
	 baseDisk(base),
	 topDisk(top)
{
	baseDisk.setOrientation(GLU_INSIDE);
	topDisk.setOrientation(GLU_OUTSIDE);
}

Cylinder::~Cylinder() {
}

void Cylinder::draw()
{
	SimpleCylinder::draw();
	baseDisk.draw();
	glTranslated(0, 0, height);
	topDisk.draw();
}


