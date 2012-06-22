/*
 * Color.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <GL/glut.h>

class Color {
protected:
	double color[4];
public:
	Color();
	Color(double, double, double, double);
	Color(int, int, int);
	virtual ~Color();
	void rgba(double, double, double, double);
	void rgb(int, int, int);
	void setColor(Color c);
	inline const double* getVect() { return color; };
	inline int getAlfa() { return color[3]; };
	inline void setAlfa(double a) { color[3] = a; };
	inline void setGL() { glColor4dv(color); };
};

#endif /* COLOR_H_ */
