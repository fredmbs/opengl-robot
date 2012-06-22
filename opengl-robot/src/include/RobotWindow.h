/*
 * RobotWindow.h
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef ROBOTWINDOW_H_
#define ROBOTWINDOW_H_

#include "WindowControl.h"
#include "Position.h"
#include "Robot.h"
#include "Text.h"
#include "CubicCage.h"
#include "Robot.h"
#include "Color.h"

class RobotWindow: public WindowControl {
private:
	double platWidth, platHeight, platDeep;
	Position eye, lookAt;
	GC::Rectangle platform;
	Robot robot;
	Text textLives, textGameOver, textFps;
	double cameraRadius, cameraLongitude, cameraLatitude;
	void setCameraPosition(double, double);
	double mouseX, mouseY;
	int mouseButton, mouseState;
	int eventFlying, eventReset;
	unsigned int interval;
	CubicCage borderland;
	bool drawCage;
	Color platformColor;
protected:
	virtual void display();
	virtual void reshape(int width, int height);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void specialKey(int key, int x, int y);
	virtual void mouse(int button, int state, int x, int y);
	virtual void mouseMove(int x, int y);
	virtual void mouseWheel(int wheel, int direction, int x, int y);
	virtual unsigned int event(int id);
public:
	RobotWindow(double, double, double);
	virtual ~RobotWindow();
	void rotateCamera(double);
	void resetCamera();
	virtual void configure();
	void setFPS(unsigned int);
	bool animateReset();
};

#endif /* ROBOTWINDOW_H_ */
