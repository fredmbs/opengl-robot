/*
 * GroupShape.h
 *
 *  Created on: 13/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef GROUPSHAPE_H_
#define GROUPSHAPE_H_

#include "Shape.h"
#include <list>

class ShapeGroup: public Shape {
private:
	std::list<Shape*> parts;
public:
	ShapeGroup();
	virtual ~ShapeGroup();
	void add(Shape*);
	virtual void draw();
};

#endif /* GROUPSHAPE_H_ */
