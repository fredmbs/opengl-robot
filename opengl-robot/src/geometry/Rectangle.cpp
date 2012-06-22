/*
 * Rectangle.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#include "Rectangle.h"

using namespace GC;

Rectangle::Rectangle(double x, double y, double z)
	: GeometryShape()
{
	this->width = x;
	this->height = y;
	this->deep = z;
}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

void Rectangle::draw()
{
	glBegin(GL_QUADS);
	//
	glNormal3d(1, 0, 0);
	glVertex3d(width, 0, deep);
	glVertex3d(width, 0, 0);
	glVertex3d(width, height, 0);
	glVertex3d(width, height, deep);
	//
	glNormal3d(0, 1, 0);
	glVertex3d(width, height, deep);
	glVertex3d(width, height, 0);
	glVertex3d(0, height, 0);
	glVertex3d(0, height, deep);
	//
	glNormal3d(0, 0, 1);
	glVertex3d(width, height, deep);
	glVertex3d(0, height, deep);
	glVertex3d(0, 0, deep);
	glVertex3d(width, 0, deep);
	//
	glNormal3d(-1, 0, 0);
	glVertex3d(0, 0, deep);
	glVertex3d(0, height, deep);
	glVertex3d(0, height, 0);
	glVertex3d(0, 0, 0);
	//
	glNormal3d(0, -1, 0);
	glVertex3d(0, 0, deep);
	glVertex3d(0, 0, 0);
	glVertex3d(width, 0, 0);
	glVertex3d(width, 0, deep);
	//
	glNormal3d(0, 0, -1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, height, 0);
	glVertex3d(width, height, 0);
	glVertex3d(width, 0, 0);
	glEnd();

}
