/*
 * Propeller.cpp
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#include "Propeller.h"
#include "Maths.h"

Propeller::Propeller(double _width, double _height, double _deep) {
	width = _width;
	height = _height;
	deep = _deep;
	frontRadius = height/2;
	front = new Cylinder(frontRadius, width);

	p[0][2] =     0; p[0][1] = -frontRadius; p[0][0] = 0;
	p[1][2] =     0; p[1][1] =  frontRadius; p[1][0] = 0;
	p[2][2] =     0; p[2][1] = -frontRadius; p[2][0] = deep;
	p[3][2] = width; p[3][1] = -frontRadius; p[3][0] = 0;
	p[4][2] = width; p[4][1] =  frontRadius; p[4][0] = 0;
	p[5][2] = width; p[5][1] = -frontRadius; p[5][0] = deep;

	n[0][2] = -1; n[0][1] =  0; n[0][0] = 0;
	n[1][2] =  0; n[1][1] = -1; n[1][0] = 0;
	n[2][2] = +1; n[2][1] =  0; n[2][0] = 0;

	double v[3][3];
	v[0][0] = p[1][0]; v[0][1] = p[1][1]; v[0][2] = p[1][2];
	v[1][0] = p[2][0]; v[1][1] = p[2][1]; v[1][2] = p[2][2];
	v[2][0] = p[4][0]; v[2][1] = p[4][1]; v[2][2] = p[4][2];
	calcNormal(v, n[3]);
	n[3][0] = -n[3][0]; n[3][1] = -n[3][1]; n[3][2] = -n[3][2];

}

Propeller::~Propeller() {
	delete front;
}

void Propeller::draw() {
	glRotated(90,1,0,0);
	glPushMatrix();
	front->draw();
	glPopMatrix();
	glBegin(GL_TRIANGLES);

	glNormal3dv(n[0]);
	glVertex3dv(p[0]);
	glVertex3dv(p[1]);
	glVertex3dv(p[2]);

	glNormal3dv(n[1]);
	glVertex3dv(p[0]);
	glVertex3dv(p[2]);
	glVertex3dv(p[3]);

	glNormal3dv(n[1]);
	glVertex3dv(p[3]);
	glVertex3dv(p[2]);
	glVertex3dv(p[5]);

	glNormal3dv(n[2]);
	glVertex3dv(p[4]);
	glVertex3dv(p[3]);
	glVertex3dv(p[5]);


	glNormal3dv(n[3]);
	glVertex3dv(p[4]);
	glVertex3dv(p[5]);
	glVertex3dv(p[2]);
	glNormal3dv(n[3]);
	glVertex3dv(p[4]);
	glVertex3dv(p[2]);
	glVertex3dv(p[1]);
	glEnd();
}
