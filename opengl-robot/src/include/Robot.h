/*
 * robot.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Position.h"
#include "ShapeGroup.h"
#include "RobotDimensions.h"
#include "RobotBase.h"
#include "RobotArm.h"
#include "RobotArmBase.h"
#include "RobotClaw.h"
#include "RobotArea.h"
#include "Rectangle.h"

class Robot: public Shape {
private:
	friend class RobotWindow;

	RobotDimensions rd;
	Position pos, initialPos;

	RobotBase base;
	RobotArmBase armBase;
	RobotArm arm;
	RobotClaw claw;

	double baseX, baseY, baseZ, maxX, maxY, maxZ, minX, minY, minZ;
	double minBaseX, minBaseZ, maxBaseX, maxBaseZ;
    bool flying, alive;
    double step;
    int lives;
    double propellerAceleration;
	inline void checkMovement();

    bool landingSafePosition;
public:
    Robot(int, GC::Rectangle&);
	virtual ~Robot();
	virtual void draw();
	void setPosition(const Position&);
	void setMovementStep(double);
	void configureLookAt(Position&);
	void moveLeft();
	void moveRight();
	void moveBack();
	void moveFront();
	bool startFlying();
	bool stopFlying();
	void moveUp();
	void moveDown();
	void revive();
	void aceleratePropeller(double);
	bool isInBase();
	bool isOverBase();
	bool isUnderBase();
	bool isInBaseProjection();
	inline bool isFlying() { return flying; };
	inline bool isAlive() { return alive; };
	inline int getLives() { return lives; };
	bool isFloating();

	bool animateStartFlying();
	bool animateFlying();
	bool animateStopFlying();
	bool animateTakingOff();
	bool animateLanding();
	bool animateRescue();
	bool animateSafeLanding();
	bool animateGoingInitialPosition();
	bool animateInitialAngles();

	bool detectedColision;
	RobotArea flyingArea;
	bool hasBaseColision();
};

bool approximate(double &val, const double inc, const double target);
bool circularApproximate(double &val, const double inc, const double target);

#endif /* ROBOT_H_ */
