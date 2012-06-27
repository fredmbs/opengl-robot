/*
 * RobotClaw.h
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTCLAW_H_
#define ROBOTCLAW_H_

#include "Shape.h"
#include "RobotHand.h"
#include "RobotFinger.h"
#include "RobotPart.h"

class RobotClaw: public RobotPart {
private:
	friend class RobotWindow;
	friend class Robot;

	RobotHand hand;
	RobotFinger finger;
	double propAngle;
public:
	RobotClaw(const RobotDimensions&);
	virtual ~RobotClaw();
	virtual void draw();
	virtual void setRotation(double);
	void setHandColor(const Color&);
	void setFingerColor(const Color&);
	void setAngle(double);
	void rotateAngle(double);
	void setAttack(double);
	void rotateAttack(double);
	inline double getAngle() { return propAngle; };
	inline double getAttack() { return hand.getRotation(); };
};

#endif /* ROBOTCLAW_H_ */
