/*
 * RobotHand.h
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTHAND_H_
#define ROBOTHAND_H_

#include "Propeller.h"
#include "Ring.h"
#include "RobotDimensions.h"
#include "RobotPart.h"

class RobotHand: public RobotPart {
private:
public:
	Propeller prop;
	Ring ring;
	Ring ringFinger;
	RobotHand(const RobotDimensions&);
	virtual ~RobotHand();
	virtual void draw();
	virtual void setRotation(double);
};

#endif /* ROBOTHAND_H_ */
