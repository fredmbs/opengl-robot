/*
 * Color.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#include "Color.h"

Color::Color() {
	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	color[3] = 1.0;
}

Color::Color(double ri, double gi, double bi, double ai) {
	color[0] = ri;
	color[1] = gi;
	color[2] = bi;
	color[3] = ai;
}

Color::Color(int ri, int gi, int bi) {
	color[0] = (double)ri/255.0;
	color[1] = (double)gi/255.0;
	color[2] = (double)bi/255.0;
	color[3] = 1;
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}

void Color::rgb(int ri, int gi, int bi) {
	color[0] = (double)ri/255.0;
	color[1] = (double)gi/255.0;
	color[2] = (double)bi/255.0;
	color[3] = 1.0;
}

void Color::rgba(double ri, double gi, double bi, double ai) {
	color[0] = ri;
	color[1] = gi;
	color[2] = bi;
	color[3] = ai;
}

void Color::setColor(Color c) {
	const double* vect = c.getVect();
	color[0] = vect[0];
	color[1] = vect[1];
	color[2] = vect[2];
	color[3] = vect[3];
}

