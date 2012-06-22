/*
 * Text.h
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include "Shape.h"
#include "Color.h"
#include "Position.h"

class Text: public Shape, public Color, public Position {
private:
	std::string message;
	Position pos;
	GLvoid *font_style;
public:
	Text();
	virtual ~Text();
	void setFontStyle(GLvoid *);
	void setText(std::string&);
	void setText(const char* format, ...);
	virtual void draw();
	void draw2D();
};

#endif /* TEXT_H_ */
