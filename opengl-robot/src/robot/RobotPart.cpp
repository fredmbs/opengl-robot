/*
 * RobotPart.cpp
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#include <cmath>
#include "RobotPart.h"

RobotPart::RobotPart(const RobotDimensions& rdim)
	: rd(rdim)
{
	angle = 0;

}

RobotPart::~RobotPart() {
	// TODO Auto-generated destructor stub
}

void RobotPart::rotate(double a) {
	setRotation(angle + a);
}

void RobotPart::setRotation(double a) {
	angle = fmod(a, 360.0);
}
