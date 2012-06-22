/*
 * RobotArmBase.h
 *
 *  Created on: 18/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTARMBASE_H_
#define ROBOTARMBASE_H_

#include "Cylinder.h"
#include "Ring.h"
#include "RobotDimensions.h"
#include "RobotPart.h"

class RobotArmBase: public RobotPart {
private:
	Cylinder armBase;
	Ring armBaseJoint;
public:
	RobotArmBase(const RobotDimensions&);
	virtual ~RobotArmBase();
	virtual void draw();
};


#endif /* ROBOTARMBASE_H_ */
