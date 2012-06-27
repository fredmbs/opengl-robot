/*
 * RobotHand.cpp
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotHand.h"
#include <iostream>

RobotHand::RobotHand(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  prop(rd.handWidth, rd.handHeight, rd.handDeep),
	  ring(rd.ringRadius, rd.ringHeight, rd.ringInnerRadius),
	  ringFinger(rd.ringFingerRadius, rd.ringFingerHeight, rd.ringFingerInnerRadius)
{

}

RobotHand::~RobotHand() {
	// TODO Auto-generated destructor stub
}

void RobotHand::draw() {
	glColor4dv(color);
	glTranslated(0, 0, -rd.ringHeight);
	ring.draw();

	glPushMatrix();
		glTranslated(rd.ringRadius, 0, rd.handHeight/2);
		glRotated(90 - angle, 1, 0, 0);
		glRotated(90, 0, 0, 1);
		prop.draw();
	glPopMatrix();

	glTranslated(rd.handWidth + rd.ringRadius + rd.ringFingerRadius, -rd.ringFingerCenterY, rd.ringFingerRadius);
	glRotated(90, 1, 0, 0);
	ringFinger.draw();
	glTranslated(0, 0, -2*rd.ringFingerHeight);
	ringFinger.draw();
}

void RobotHand::setRotation(double a) {
	RobotPart::setRotation(a);
	if (angle > 90)
		angle = 90;
	else if (angle < 0)
		angle = 0;
}
