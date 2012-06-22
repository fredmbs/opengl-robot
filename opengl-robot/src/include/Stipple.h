/*
 * Stipple.h
 *
 *  Created on: 20/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef STIPPLE_H_
#define STIPPLE_H_

#include <GL/glut.h>

class Stipple {
protected:
	GLubyte stipple[128];
public:
	Stipple();
	virtual ~Stipple();
	inline void setGL() {
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(stipple);
	};
	inline void unsetGL() {
		glDisable(GL_POLYGON_STIPPLE);
	};
};

#endif /* STIPPLE_H_ */
