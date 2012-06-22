/*
 * Ring.cpp
 *
 *  Created on: 14/06/2012
 *      Author: Frederico Sampaio
 */

#include "Ring.h"

Ring::Ring(double radius, double height, double innerRadius)
	:Cylinder(radius, height),
	 innerCylinder(innerRadius, height)
{
	baseDisk.setInnerRadius(innerRadius);
	topDisk.setInnerRadius(innerRadius);
	innerCylinder.setOrientation(GLU_INSIDE);
}

Ring::~Ring() {
}

double Ring::getInnerRadius() { return baseDisk.getInnerRadius(); };

void Ring::draw()
{
	glPushMatrix();
	Cylinder::draw();
	glPopMatrix();
	innerCylinder.draw();
}
