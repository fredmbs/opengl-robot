/*
 * Text.cpp
 *
 *  Created on: 16/06/2012
 *      Author: Frederico Sampaio
 */

#include <stdio.h>
#include <stdarg.h>

#include "Text.h"

Text::Text()
	: message()
{
	font_style = GLUT_BITMAP_HELVETICA_12;
}

Text::~Text() {
}

//  Pointer to a font style..
//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
//

void Text::setFontStyle(GLvoid *fs) {
	font_style = fs;
}

//----------------------------------------------------------------------------
void Text::setText(std::string& msg)
{
	message = msg;
}

void Text::setText(const char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	char* text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of
	// arguments. _vscprintf doesn't count terminating '\0' (that's why +1)
	//len = _vscprintf(format, args) + 1;
	// !! RETIRADO !! incompatibilidade com o LINUX
	// estabelece um buffer de 256 bytes que é mais do que suficiente para a atual aplicação
	len = 256;

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len);

	//  Write formatted output using a pointer to the list of arguments
	//vsprintf_s(text, len, format, args);
	vsprintf(text, format, args);

	//  End using variable argument list
	va_end(args);

	//
	message = text;

    //  Free the allocated memory for the string
	free(text);
}

void Text::draw()
{
	// Imprime o texto
	// cor do texto
	Color::setGL();
	//  Specify the raster position for pixel operations.
	glRasterPos3d (x, y, z);
	//
	const char *text = message.c_str();
	//  Draw the characters one by one
	for (int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);
	// Retorna o sistema de coordenadas do modelo
}

void Text::draw2D()
{
	// Salva o sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		// Zera o sistema de coordenadas de proje��o
		glLoadIdentity();
		// Salva sistema de coordenadas do modelo
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			// Zera o sistema de coordenadas do modelo
			glLoadIdentity();
			draw();
		glPopMatrix();
	// Retorna o sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// retonra para a matriz de modelo
	glMatrixMode(GL_MODELVIEW);
}
