/*
 * SimpleCylinder.cpp
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#include "SimpleCylinder.h"

SimpleCylinder::SimpleCylinder(double radius, double height)
	:GeometryShape()
{
	base = radius;
	top = radius;
	this->height = height;
	slices = 60;
	stacks = 60;
}

SimpleCylinder::~SimpleCylinder() {
}

double SimpleCylinder::getRadius() { return base; };
double SimpleCylinder::getHeight() { return height; };

void SimpleCylinder::draw() {
	gluCylinder(quad, base, top, height, slices, stacks);
}
