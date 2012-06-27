/*
 * RobotPart.h
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTPART_H_
#define ROBOTPART_H_

#include "Shape.h"
#include "RobotDimensions.h"
#include "Color.h"

class RobotPart: public Shape, public Color {
protected:
	const RobotDimensions& rd;
	double angle;
public:
	RobotPart(const RobotDimensions&);
	virtual ~RobotPart();
	void rotate(double);
	virtual void setRotation(double);
	inline double getRotation() { return angle; };
};

#endif /* ROBOTPART_H_ */
