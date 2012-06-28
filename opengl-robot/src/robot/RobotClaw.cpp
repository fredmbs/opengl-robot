/*
 * RobotClaw.cpp
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotClaw.h"

RobotClaw::RobotClaw(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  hand(rd),
	  finger(rd)
{
	propAngle = 0;
}

RobotClaw::~RobotClaw() {
}

void RobotClaw::setAngle(double a) {
	propAngle = a;
	if (propAngle < 0)
		propAngle = 0;
	else if (propAngle > 90)
		propAngle = 90;
}

void RobotClaw::rotateAngle(double a) {
	setAngle(propAngle + a);
}

void RobotClaw::setAttack(double a) {
	hand.setRotation(a);
}

void RobotClaw::rotateAttack(double a) {
	hand.rotate(a);
}

void RobotClaw::setHandColor(const Color& c) {
	hand.setColor(c);
}

void RobotClaw::setFingerColor(const Color& c) {
	finger.setColor(c);
}

void RobotClaw::setRotation(double a) {
	RobotPart::setRotation(a);
	if (angle < 0)
		angle += 360;
	if (angle < 283 && angle > 77) {
		if (angle > 180)
			angle = 283;
		else
			angle = 77;
	}
}

void RobotClaw::draw() {

	glPushMatrix();
		glRotated(angle + propAngle, 0, 0, 1);
		hand.draw();
		finger.draw();
	glPopMatrix();

	glPushMatrix();
		glRotated(angle - propAngle, 0, 0, 1);
		glRotated(180, 1, 0, 0);
		glTranslated(0, 0, -rd.ringHeight);
		hand.draw();
		finger.draw();
	glPopMatrix();

}

