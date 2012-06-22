/*
 * RobotBase.h
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTBASE_H_
#define ROBOTBASE_H_

#include "Shape.h"
#include "Rectangle.h"
#include "Cylinder.h"
#include "Ring.h"
#include "RobotDimensions.h"
#include "RobotPart.h"

class RobotBase: public RobotPart {
private:
	GC::Rectangle base;
public:
	RobotBase(const RobotDimensions&);
	virtual ~RobotBase();
	virtual void draw();
};

#endif /* ROBOTBASE_H_ */
