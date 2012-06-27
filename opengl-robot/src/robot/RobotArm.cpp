/*
 * RobotArm.cpp
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotArm.h"

RobotArm::RobotArm(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  arm(rd.armWidth, rd.armHeight, rd.armDeep),
	  ring(rd.ringRadius, rd.ringHeight, rd.ringInnerRadius)
{

}

RobotArm::~RobotArm() {
}

void RobotArm::draw() {
	glColor4dv(color);
	glRotated(angle, 0,0,1);
	glTranslated(0, 0, -rd.ringHeight);
	ring.draw();
	glTranslated(0, 0, rd.armDeep - rd.ringHeight);
	ring.draw();
	glTranslated(rd.ringRadius, -rd.ringRadius, -(rd.armDeep - rd.ringHeight));
	arm.draw();
	glTranslated(rd.armWidth + rd.ringRadius, rd.ringRadius, rd.ringHeight);
	ring.draw();
}

void RobotArm::setRotation(double a) {
	RobotPart::setRotation(a);
	if (angle > 180)
		angle = 180;
	else if (angle < 0)
		angle = 0;
}
