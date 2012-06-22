/*
 * VisualForm.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef VISUALFORM_H_
#define VISUALFORM_H_

class Shape {
public:
	Shape();
	virtual ~Shape();
	virtual void draw() = 0;
};

#endif /* VISUALFORM_H_ */
