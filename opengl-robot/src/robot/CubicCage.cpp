/*
 * Cage.cpp
 *
 *  Created on: 17/06/2012
 *      Author: Frederico Sampaio
 */

#include <GL/glut.h>
#include "CubicCage.h"

CubicCage::CubicCage(double qSize, double tSize)
	: Shape()
{
	quadSize = qSize;
	numQuads = tSize/qSize;
}

CubicCage::~CubicCage() {
	// TODO Auto-generated destructor stub
}

void CubicCage::draw()
{
	double s = quadSize * numQuads;
	double startPos = -s/2;
	// eixo x
	glPushMatrix();
	glTranslated(startPos, startPos, startPos);
	for (int i = 0; i <= numQuads; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, s);
		glVertex3d(0, s, s);
		glVertex3d(0, s, 0);
		glEnd();
		glTranslated(quadSize, 0, 0);
	}
	glPopMatrix();
	// eixo y
	glPushMatrix();
	glTranslated(startPos, startPos, startPos);
	for (int i = 0; i <= numQuads; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, s);
		glVertex3d(s, 0, s);
		glVertex3d(s, 0, 0);
		glEnd();
		glTranslated(0, quadSize, 0);
	}
	glPopMatrix();
	// eixo z
	glPushMatrix();
	glTranslated(startPos, startPos, startPos);
	for (int i = 0; i <= numQuads; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(0, 0, 0);
		glVertex3d(s, 0, 0);
		glVertex3d(s, s, 0);
		glVertex3d(0, s, 0);
		glEnd();
		glTranslated(0, 0, quadSize);
	}
	glPopMatrix();
}
