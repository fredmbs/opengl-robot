/*
 * RobotArm.h
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTARM_H_
#define ROBOTARM_H_

#include "Shape.h"
#include "Rectangle.h"
#include "Ring.h"
#include "RobotDimensions.h"
#include "RobotPart.h"

class RobotArm: public RobotPart {
private:
public:
	GC::Rectangle arm;
	Ring ring;
	RobotArm(const RobotDimensions&);
	virtual ~RobotArm();
	virtual void draw();
	virtual void setRotation(double);
};

#endif /* ROBOTARM_H_ */
