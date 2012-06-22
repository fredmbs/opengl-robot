/*
 * Position.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <GL/glut.h>

class Position {
public:
	double x, y, z;
	Position();
	virtual ~Position();
	inline void setGL() { glTranslated(x, y, z);};
	inline void setPosition(double _x, double _y, double _z)
		{ x = _x; y = _y; z = _z; };
	double dist(Position*);
};

#endif /* POSITION_H_ */
