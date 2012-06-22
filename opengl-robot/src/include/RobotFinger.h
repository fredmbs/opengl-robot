/*
 * RobotFinger.h
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTFINGER_H_
#define ROBOTFINGER_H_

#include "Shape.h"
#include "Ring.h"
#include "Rectangle.h"
#include "RobotDimensions.h"
#include "RobotPart.h"

class RobotFinger: public RobotPart {
private:
	friend class Robot;

	Ring ring;
	GC::Rectangle proximalPhalanx, middlePhalanx, distalPhalanx;
public:
	RobotFinger(const RobotDimensions&);
	virtual ~RobotFinger();
	virtual void rotate(double);
	void setRotation(double);
	virtual void draw();
};

#endif /* ROBOTFINGER_H_ */
