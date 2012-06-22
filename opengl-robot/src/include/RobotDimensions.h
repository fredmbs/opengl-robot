/*
 * RobotDimensions.h
 *
 *  Created on: 15/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTDIMENSIONS_H_
#define ROBOTDIMENSIONS_H_

class RobotDimensions {
public:
	double armWidth, armHeight, armDeep;
	double ringHeight, ringRadius, ringInnerRadius, ringCenterZ;
	double ringFingerHeight, ringFingerRadius;
	double ringFingerInnerRadius, ringFingerCenterY;
	double baseWidth, baseHeight, baseDeep;
	double baseCenterX, baseCenterZ;
	double armBaseRadius, armBaseHeight;
	double armBaseX, armBaseY, armBaseZ;
	double handWidth, handHeight, handDeep;
	double fingerHeight, fingerDeep, fingerCenterY;
	double pPhalanxWidth, mPhalanxWidth, dPhalanxWidth;
	double fingerPMJointAngle, fingerMDJointAngle;

	double maxPropellerRadius;
	double rectFlyingWidth, rectFlyingHeight, rectFlyingDeep;
	double rectFlyingDx, rectFlyingDz;

	RobotDimensions(double, double, double);
	virtual ~RobotDimensions();
};

#endif /* ROBOTDIMENSIONS_H_ */
