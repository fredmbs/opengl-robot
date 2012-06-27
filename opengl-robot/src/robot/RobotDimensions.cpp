/*
 * RobotDimensions.cpp
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#include "RobotDimensions.h"
#include "Maths.h"

#define MAX(a,b) ((a>b)?a:b)

RobotDimensions::RobotDimensions(double _armWidth, double _armHeight, double _armDeep) {
	armWidth = _armWidth;
	armHeight = _armHeight;
	armDeep = _armDeep;
	ringHeight = armDeep/3;
	ringRadius = armHeight/2;
	ringInnerRadius =  ringRadius / 2;
	ringCenterZ = ringHeight/2;
	baseWidth = (4 * armDeep);
	baseHeight = armWidth;
	baseDeep = 2 * armDeep;
	baseCenterX = baseWidth / 2;
	baseCenterZ = baseDeep / 2;
	armBaseRadius = armDeep/1.7;
	armBaseHeight = armDeep;
	armBaseX = armDeep * 3;
	armBaseY = armWidth;
	armBaseZ = armDeep;
	handWidth = armWidth;
	handHeight = armHeight/2;
	handDeep = armDeep - handHeight;
	ringFingerHeight = handHeight/3;
	ringFingerRadius = handHeight/2;
	ringFingerInnerRadius =  ringFingerRadius / 2;
	ringFingerCenterY = ringFingerHeight/2;

	pPhalanxWidth = armDeep/2;
	fingerHeight = ringFingerRadius * 1.5;
	fingerDeep = ringFingerHeight;
	fingerCenterY = ringFingerRadius + (ringFingerRadius - fingerHeight)/2;

	double d = handDeep;
	double z = pPhalanxWidth / 2;
	double h = sqrt((d*d)+(z*z));
	fingerPMJointAngle = asin(z/h);
	dPhalanxWidth = (fingerHeight/2)/sin(fingerPMJointAngle);
	mPhalanxWidth = (d-dPhalanxWidth)/cos(fingerPMJointAngle);
	fingerMDJointAngle = (M_PI/2) - fingerPMJointAngle;

	fingerPMJointAngle = (180/M_PI) * fingerPMJointAngle;
	fingerMDJointAngle = (180/M_PI) * fingerMDJointAngle;

	maxPropellerRadius = ringRadius  + handWidth + ringFingerRadius + 2*pPhalanxWidth;
	rectFlyingWidth = MAX(armBaseX, maxPropellerRadius) + maxPropellerRadius;
	rectFlyingHeight = baseHeight + armBaseHeight + armWidth + MAX(handHeight, handDeep) + ringRadius;
	rectFlyingDeep = MAX(baseDeep, 2* maxPropellerRadius);
	rectFlyingDx = -MAX(baseCenterX, baseCenterX + maxPropellerRadius - armBaseX);
	rectFlyingDz = -rectFlyingDeep/2;

}

RobotDimensions::~RobotDimensions() {
	// TODO Auto-generated destructor stub
}

