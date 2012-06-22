/*
 * GeometryForm.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef GEOMETRYSHAPE_H_
#define GEOMETRYSHAPE_H_

#include <GL/glut.h>
#include "Color.h"
#include "Shape.h"

class GeometryShape: public Shape {
protected:
	GLUquadricObj *quad;
public:
	GeometryShape();
	virtual ~GeometryShape();
	void setOrientation(GLenum);
};

#endif /* GEOMETRYSHAPE_H_ */
