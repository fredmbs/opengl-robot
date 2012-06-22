/*
 * RobotFinger.cpp
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotFinger.h"

RobotFinger::RobotFinger(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  ring(rd.ringFingerRadius, rd.ringFingerHeight, rd.ringFingerInnerRadius),
	  proximalPhalanx(rd.pPhalanxWidth, rd.fingerHeight, rd.fingerDeep),
	  middlePhalanx(rd.mPhalanxWidth, rd.fingerHeight, rd.fingerDeep),
	  distalPhalanx(rd.dPhalanxWidth, rd.fingerHeight, rd.fingerDeep)
{
}

RobotFinger::~RobotFinger() {
}

void RobotFinger::draw() {
	glColor4dv(color);
	glRotated(angle, 0, 0, 1);
	glTranslated(0, 0, rd.ringFingerHeight);
	ring.draw();
	glTranslated(rd.ringFingerRadius - rd.ringFingerInnerRadius, -rd.fingerCenterY, 0);
	proximalPhalanx.draw();
	glTranslated(rd.pPhalanxWidth, 0, 0);
	glRotated(rd.fingerPMJointAngle, 0, 0, 1);
	middlePhalanx.draw();
	glTranslated(rd.mPhalanxWidth, 0, 0);
	glRotated(rd.fingerMDJointAngle, 0, 0, 1);
	distalPhalanx.draw();
}

void RobotFinger::rotate(double a) {
	setRotation(a + angle);
}

void RobotFinger::setRotation(double a) {
	RobotPart::setRotation(a);
	if(angle > 0) angle = 0;
	else if(angle < -90) angle = -90;
}
