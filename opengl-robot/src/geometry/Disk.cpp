/*
 * Disk.cpp
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#include "Disk.h"

Disk::Disk(double radius)
	: GeometryShape()
{
	innerRadius = 0;
	outerRadius = radius;
	diskSlices = 40;
	diskStacks = 40;
}

Disk::~Disk() {
	gluDeleteQuadric(quad);
}

double Disk::getInnerRadius() { return innerRadius; };

void Disk::setInnerRadius(double radius) {
	innerRadius = radius;
}

void Disk::draw() {
	gluDisk(quad, innerRadius, outerRadius, diskSlices, diskStacks);
}
