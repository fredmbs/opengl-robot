/*
 * RobotArea.cpp
 *
 *  Created on: 20/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotArea.h"

RobotArea::RobotArea(const RobotDimensions& rdim)
	: RobotPart(rdim),
	  GC::Rectangle(rd.rectFlyingWidth, rd.rectFlyingHeight, rd.rectFlyingDeep)
{
}

RobotArea::~RobotArea() {
}

void RobotArea::draw() {
	glPushMatrix();
	glColor4d(0.8, 0.8, 0.8, 0.25);
	stipple.setGL();
	glTranslated(rd.rectFlyingDx, 0, rd.rectFlyingDz);
	Rectangle::draw();
	stipple.unsetGL();
	glPopMatrix();
}

#define _IN(p,a,b) (((p)>(a)) && ((p)<(b)))
#define COLIDE(p,q,a,b) (_IN(p,a,b) || _IN(q,a,b) || _IN(a,p,q) || _IN(b,p,q))

bool RobotArea::hasBaseColision(const Position& robotPos, double _x, double _y, double _z) {
	double minRobot = robotPos.y;
	double maxRobot = minRobot + height;
	if (COLIDE(minRobot, maxRobot, 0, _y)) {
		minRobot = robotPos.x + rd.rectFlyingDx;
		maxRobot = minRobot + width;
		if (COLIDE(minRobot, maxRobot, 0, _x)) {
			minRobot = robotPos.z + rd.rectFlyingDz;
			maxRobot = minRobot + deep;
			return (COLIDE(minRobot, maxRobot, 0, _z));
		}
	}
	return false;
}
