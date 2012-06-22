/*
 * Disk.h
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef DISK_H_
#define DISK_H_

#include "GeometryShape.h"

class Disk: public GeometryShape {
protected:
	double innerRadius, outerRadius;
	int diskSlices, diskStacks;
public:
	Disk(double radius);
	virtual ~Disk();
	double getInnerRadius();
	void setInnerRadius(double);
	virtual void draw();
};

#endif /* DISK_H_ */
