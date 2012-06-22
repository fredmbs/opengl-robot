/*
 * RobotArea.h
 *
 *  Created on: 20/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTAREA_H_
#define ROBOTAREA_H_

#include "Stipple.h"
#include "RobotPart.h"
#include "Rectangle.h"
#include "Position.h"

class RobotArea: public RobotPart, public GC::Rectangle {
private:
	Stipple stipple;
public:
	RobotArea(const RobotDimensions&);
	virtual ~RobotArea();
	virtual void draw();
	bool hasBaseColision(const Position&, double x, double y, double z);
};

#endif /* ROBOTAREA_H_ */
