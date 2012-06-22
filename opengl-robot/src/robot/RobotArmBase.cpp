/*
 * RobotArmBase.cpp
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotArmBase.h"

RobotArmBase::RobotArmBase(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  armBase(rd.armBaseRadius, rd.armBaseHeight),
	  armBaseJoint(rd.ringRadius, rd.ringHeight, rd.ringInnerRadius)
{

}

RobotArmBase::~RobotArmBase() {
	// TODO Auto-generated destructor stub
}

void RobotArmBase::draw() {
	glColor4dv(color);
	glPushMatrix();
		glTranslated(rd.armBaseX, rd.armBaseY, rd.armBaseZ);
		glRotated(270, 1, 0, 0);
		glRotated(angle, 0, 0, 1);
		armBase.draw();
	glPopMatrix();
	glTranslated(rd.armBaseX, rd.armBaseY + rd.armBaseHeight + rd.ringRadius, rd.armBaseZ);
	glRotated(angle, 0, 1, 0);
	glTranslated(0, 0, -rd.ringCenterZ);
	armBaseJoint.draw();
}
