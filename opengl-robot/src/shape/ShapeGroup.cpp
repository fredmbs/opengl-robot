/*
 * GroupShape.cpp
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#include <GL/glut.h>
#include "ShapeGroup.h"

ShapeGroup::ShapeGroup() {
}

ShapeGroup::~ShapeGroup() {
}

void ShapeGroup::draw() {
	glPushMatrix();
	std::list<Shape*>::const_iterator shape = parts.begin();
	for(; shape != parts.end(); ++shape) {
		(*shape)->draw();
	}
	glPopMatrix();
}

void ShapeGroup::add(Shape* _shape) {
	parts.push_back(_shape);
}
