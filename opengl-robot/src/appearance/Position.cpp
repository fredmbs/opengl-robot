/*
 * Position.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#include "Position.h"
#include <cmath>

Position::Position() {
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

double Position::dist(Position* Q) {
	return sqrt(pow(this->x - Q->x, 2)
			  + pow(this->y - Q->y, 2)
			  + pow(this->z - Q->z,2));
}

