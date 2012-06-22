/*
 * robot.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#include <cmath>
#include "Robot.h"
#include "RobotArm.h"
#include "RobotBase.h"
#include "RobotDimensions.h"
#include "RobotClaw.h"
#include "Rectangle.h"

#define DEFAULT_STEP     0.1
#define FLYING_STEP      0.2

Robot::Robot(int initialLives, GC::Rectangle& _platform)
	: rd(1, 0.2, 0.4),
	  pos(), initialPos(),
	  base(rd),
	  armBase(rd),
	  arm(rd),
	  claw(rd),
	  flyingArea(rd)
{
    lives = initialLives;
    step = DEFAULT_STEP;
	baseX = _platform.getWidth();
	baseY = _platform.getHeight();
	baseZ = _platform.getDeep();
	maxX = maxY = maxZ = 100;
	minX = minY = minZ = -100;
    minBaseX = rd.baseWidth / 2;
    minBaseZ = rd.baseDeep / 2;
    maxBaseX = baseX - minBaseX;
    maxBaseZ = baseZ - minBaseZ;
    revive();
    initialPos = pos;
    landingSafePosition = false;

    detectedColision = false;
}

void Robot::revive() {
    flying = false;
    alive = true;
    armBase.setRotation(0);
    arm.setRotation(45);
    claw.setRotation(-45);
    claw.setAngle(0);
	claw.setAttack(0);
	claw.finger.setRotation(0);
    pos.x = (baseX - rd.baseWidth) / 2;
    pos.y = baseY;
    pos.z = (baseZ - rd.baseDeep) / 2;
}

Robot::~Robot() {
}

void Robot::draw() {
	glTranslated(pos.x, pos.y, pos.z);
	glPushMatrix();
	base.draw();
	armBase.draw();
	arm.draw();
	claw.draw();
	glPopMatrix();
	if (detectedColision)
		flyingArea.draw();
}

void Robot::setPosition(const Position& p) {
	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	checkMovement();
}

inline void Robot::checkMovement() {
	if (alive && pos.y <= minY) {
		alive = false;
		--lives;
	}
}

bool Robot::isInBase() {
	return ((pos.x >= minBaseX) && (pos.x <= maxBaseX) &&
			(pos.y == baseY) &&
			(pos.z >= minBaseZ) && (pos.z <= maxBaseZ));
}

bool Robot::isOverBase() {
	return ((pos.x >= minBaseX) && (pos.x <= maxBaseX) &&
			(pos.y >= baseY) &&
			(pos.z >= minBaseZ) && (pos.z <= maxBaseZ));
}

bool Robot::isUnderBase() {
	return ((pos.x >= minBaseX) && (pos.x <= maxBaseX) &&
			(pos.y <= (baseY - rd.baseHeight + 2.5))  &&
			(pos.z >= minBaseZ) && (pos.z <= maxBaseZ));
}

bool Robot::isInBaseProjection() {
	return ((pos.x >= (minBaseX - rd.baseWidth)) &&
			(pos.x <= (maxBaseX + rd.baseWidth)) &&
			(pos.z >= (minBaseZ - rd.baseDeep)) &&
			(pos.z <= (maxBaseZ + rd.baseDeep)));
}

void Robot::configureLookAt(Position& p) {
	p.x = rd.armDeep * 2 + pos.x;
	p.y = rd.armWidth + pos.y;
	p.z = pos.z;
}

void Robot::setMovementStep(double s) {
	step = s;
}

bool Robot::hasBaseColision() {
	detectedColision = flyingArea.hasBaseColision(pos, baseX, baseY, baseZ);
	return detectedColision;
}

void Robot::moveLeft() {
	if (pos.z > minZ) {
		pos.z -= step;
		if (isFloating()) {
			if (hasBaseColision())
				pos.z += step;
		} else
			if (pos.z < minBaseZ)
				pos.z = minBaseZ;
	}
}

void Robot::moveRight() {
	if (pos.z < maxZ) {
		pos.z += step;
		if (isFloating()) {
			if (hasBaseColision())
				pos.z -= step;
		} else
			if (pos.z > maxBaseZ)
			pos.z = maxBaseZ;
	}
}

void Robot::moveBack() {
	if (pos.x > minX) {
		pos.x -= step;
		if (isFloating()) {
			if (hasBaseColision())
				pos.x += step;
		} else
			if (pos.x < minBaseX)
				pos.x = minBaseX;
	}
}

void Robot::moveFront() {
	if (pos.x < maxX) {
		pos.x += step;
		if (isFloating()) {
			if (hasBaseColision())
				pos.x -= step;
		} else
			if (pos.x > maxBaseX)
				pos.x = maxBaseX;
	}
}

void Robot::moveUp() {
	if (isFloating() && pos.y < maxY) {
		pos.y += step;
		if (isFloating()) {
			if (hasBaseColision())
				pos.y -= step;
		} else
			checkMovement();
	}
}

void Robot::moveDown() {
	if (isFloating()) {
		pos.y -= step;
		if (isFloating()) {
			if (hasBaseColision())
				pos.y += step;
		} else
			checkMovement();
	}
}

void Robot::aceleratePropeller(double a) {
	if (flying)
		propellerAceleration += a;
}


inline bool Robot::isFloating() {
	return flying && (propellerAceleration > 10);
}

bool Robot::startFlying() {
	if (!flying) {
		flying = true;
	    detectedColision = false;
		step = FLYING_STEP;
		propellerAceleration = 0;
		return true;
	}
	return false;
}

bool Robot::stopFlying() {
	if (flying) {
		flying = false;
		step = DEFAULT_STEP;
	    detectedColision = false;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------

bool approximate(double &val, const double inc, const double target) {
	if (val == target)
		return false;
	if (val > target) {
		val -= inc;
		if (val < target)
			val = target;
	} else {
		val += inc;
		if (val > target)
			val = target;
	}
	return true;
}

// Pressup�e que inc e target sejam positivos e menores que 360!!!!
bool circularApproximate(double &val, const double inc, const double target) {
	if (val == target)
		return false;

	if ((inc < 0) || (inc > 360))
		return approximate(val, inc, target);

	if ((target < 0) || (target > 360))
		return approximate(val, inc, target);

	if (val < 0)
		val = 360.0 + fmod(val, 360.0);
	else if (val > 360)
		val = fmod(val, 360.0);

	if (fabs(val - target) < inc)
		val = target;
	else if (target < val) {
		if ((val - target) < 180) {
			val -= inc;
		} else {
			val += inc;
		}
	} else {
		if ((target - val) > 180) {
			val -= inc;
		} else {
			val += inc;
		}
	}
	return true;
}

bool Robot::animateStartFlying() {
	if (!flying) return false;
	// anima��es paralelas
	bool action1, action2;
	double angleArm = arm.getRotation();
	if ((action1 = circularApproximate(angleArm, 2, 90)))
		arm.setRotation(angleArm);
	double angleClaw = claw.getRotation();
	if ((action2 = circularApproximate(angleClaw, 2, 0)))
		claw.setRotation(angleClaw);
	// anima��es sequenciais
	if (!(action1 || action2)) {
		// novo conjunto de anima��es paralelas
		double angleProp = claw.getAngle();
		if ((action1 = circularApproximate(angleProp, 2, 90)))
			claw.setAngle(angleProp);
		double angleAttack = claw.getAttack();
		if ((action2 = circularApproximate(angleAttack, 0.2, 10)))
			claw.setAttack(angleAttack);
		if (!(action1 || action2)) {
			if (approximate(propellerAceleration, 1, 50))
				armBase.rotate(propellerAceleration);
			 else
				// se terminaram todas as anima��es, informa
				return false;
		}
	}
	// ainda existem anima��es
	// (ou existe a �ltima verifica��o na pr�xima rodada)
	return true;
}

bool Robot::animateFlying() {
	if (!flying) return false;
	armBase.rotate(propellerAceleration);
	return true;
}

bool Robot::animateInitialAngles() {
	bool action1, action2, action3, action4, action5, action6;
	// sequencia de anima��o paralela
	double angleBase = armBase.getRotation();
	if ((action1 = circularApproximate(angleBase, 2, 0)))
		armBase.setRotation(angleBase);
	double angleArm = arm.getRotation();
	if ((action2 = circularApproximate(angleArm, 2, 45)))
		arm.setRotation(angleArm);
	double angleClaw = claw.getRotation();
	if ((action3 = circularApproximate(angleClaw, 2, 315)))
		claw.setRotation(angleClaw);
	double angleFinger = claw.finger.getRotation();
	if ((action4 = circularApproximate(angleFinger, 1, 0)))
		claw.finger.setRotation(angleFinger);
	double anglePropeller = claw.getAngle();
	if ((action5 = circularApproximate(anglePropeller, 1, 0)))
		claw.setAngle(anglePropeller);
	double angleAttack = claw.getAttack();
	if ((action6 = circularApproximate(angleAttack, 1, 0)))
		claw.setAttack(angleAttack);
	return (action1 || action2 || action3 || action4 || action5 || action6);
}

bool Robot::animateStopFlying() {
	if (flying) return false;
	// anima��es sequenciais
	if (approximate(propellerAceleration, 1, 0)) {
		armBase.rotate(propellerAceleration);
	} else {
		// anima��es paralelas
		bool actionS1, actionS2;
		double angleProp = claw.getAngle();
		if ((actionS1 = circularApproximate(angleProp, 2, 0)))
			claw.setAngle(angleProp);
		double angleAttack = claw.getAttack();
		if ((actionS2 = circularApproximate(angleAttack, 0.2, 0)))
			claw.setAttack(angleAttack);
		if (!(actionS1 || actionS2)) {
			return animateInitialAngles();
		}
	}
	// ainda existem anima��es
	// (ou existe a �ltima verifica��o na pr�xima rodada)
	return true;
}

bool Robot::animateTakingOff() {
	if (!flying) return false;
	armBase.rotate(propellerAceleration);
	return approximate(pos.y, 0.05, 1 + baseY);
}

bool Robot::animateLanding() {
	if (!flying) return false;
	if (isOverBase()) {
		armBase.rotate(propellerAceleration);
		return approximate(pos.y, step, baseY);
	} else {
		if (approximate(propellerAceleration, 1, 0))
			armBase.rotate(propellerAceleration);
	}
	if (pos.y < minY) {
		lives--;
		alive = false;
		return false;
	}
	return approximate(pos.y, step*4, minY-2);
}

bool Robot::animateRescue() {
	if (!flying || isOverBase()) return false;
	if (approximate(propellerAceleration, 1, 50)) {
		armBase.rotate(propellerAceleration);
		double s = step*4;
		double dy = s - (propellerAceleration/50)*s;
		approximate(pos.y, dy, minY-2);
		if (pos.y < minY) {
			lives--;
			alive = false;
			return false;
		}
		return true;
	}
	return false;
}

bool Robot::animateSafeLanding() {
	if (!flying) return false;
	armBase.rotate(propellerAceleration);
	if (landingSafePosition) {
		// anima��es paralelas
		bool action1, action2;
		double previus = pos.x;
		action1 = approximate(pos.x, step, initialPos.x);
		if (action1 && hasBaseColision()) {
			pos.x = previus;
		}
		action2 = approximate(pos.z, step, initialPos.z);
		if (!(action1 || action2)) {
			if (!approximate(pos.y, step, initialPos.y)) {
				landingSafePosition = false;
				return false;
			}
		}
	} else {
		bool action1, action2, action3;
		double previus;
		previus = pos.x;
		if ((action1 = approximate(pos.x, step, -4))) {
			if (hasBaseColision())
				pos.x = previus;
		}
		previus = pos.y;
		if ((action2 = approximate(pos.y, step, 2))) {
			if (hasBaseColision())
				pos.y = previus;
		}
		previus = pos.z;
		if ((action3 = approximate(pos.z, step, -4))) {
			if (hasBaseColision())
				pos.z = previus;
		}
		landingSafePosition = !(action1 || action2 || action3);
	}
	return true;
}

bool Robot::animateGoingInitialPosition() {
	if (!flying && isInBase()) {
		bool action1 = approximate(pos.x, step, initialPos.x);
		bool action2 = approximate(pos.z, step, initialPos.z);
		bool action3 = animateInitialAngles();
		return (action1 || action2 || action3);
	}
	return false;
}
