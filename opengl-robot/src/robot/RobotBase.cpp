/*
 * RobotBase.cpp
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotBase.h"

RobotBase::RobotBase(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  base(rd.baseWidth, rd.baseHeight, rd.baseDeep)
{

}

RobotBase::~RobotBase() {
}

void RobotBase::draw() {
	glColor4dv(color);
	glTranslated(-rd.baseCenterX, 0, -rd.baseCenterZ);
	base.draw();
}
