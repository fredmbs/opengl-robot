/*
 * GeometryForm.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#include "GeometryShape.h"

GeometryShape::GeometryShape()
	: Shape()
{
	quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);
}

GeometryShape::~GeometryShape() {
	gluDeleteQuadric(quad);
}

void GeometryShape::setOrientation(GLenum orientation) {
	gluQuadricOrientation(quad, orientation);
}
