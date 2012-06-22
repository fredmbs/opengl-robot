/*
 * Window.cpp
 *
 *  Created on: 06/06/2012
 *      Author: Frederico Sampaio
 */

#include <GL/freeglut.h>
#include "WindowControl.h"
#include <climits>
#include <map>

typedef int(WindowControl::*eventPtr)(int);

typedef struct eventData {
	WindowControl* win;
	int id;
} Event;

int lastEventId = 0;

std::map<int, WindowControl*> windowsMap;

typedef std::map<int, Event> EventMap;
EventMap eventMap;

void WindowControl::cbDisplay() {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) {
		win->calculateFPS();
		win->display();
	}
}

void WindowControl::cbReshape(int width, int height) {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) win->reshape(width, height);
}

void WindowControl::cbKeyboard(unsigned char key, int x, int y) {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) win->keyboard(key, x, y);
}

void WindowControl::cbMouse(int button, int state, int x, int y) {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) win->mouse(button, state, x, y);
}

void WindowControl::cbSpecialKeyboard(int key, int x, int y) {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) win->specialKey(key, x, y);
}

void WindowControl::cbMouseMove(int x, int y) {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) win->mouseMove(x, y);
}

void WindowControl::cbMouseWheel(int wheel, int direction, int x, int y) {
	WindowControl* win = windowsMap[glutGetWindow()];
	if (win) win->mouseWheel(wheel, direction, x, y);
}

void WindowControl::cbTimer(int eventId) {
	std::map<int, Event>::iterator it;
	it = eventMap.find(eventId);
	if (it != eventMap.end()) {
		int msec = (*it).second.win->event((*it).second.id);
		if (msec)
			glutTimerFunc(msec, WindowControl::cbTimer, eventId);
		else
			eventMap.erase(it);
	}
}

WindowControl::WindowControl()
	: title()
{
	title = "";
    hWin = glutCreateWindow("");
    windowsMap[hWin] = this;
    glutDisplayFunc(WindowControl::cbDisplay);
    glutReshapeFunc(WindowControl::cbReshape);
    enableEvents();
    previousTime = fps = 0;
    glutGet(GLUT_ELAPSED_TIME);
}

void WindowControl::enableEvents()
{
    glutKeyboardFunc(WindowControl::cbKeyboard);
    glutSpecialFunc(WindowControl::cbSpecialKeyboard);
    glutMouseFunc(WindowControl::cbMouse);
    glutMotionFunc(WindowControl::cbMouseMove);
    glutMouseWheelFunc(WindowControl::cbMouseWheel);
}

void WindowControl::disableEvents()
{
    glutKeyboardFunc(0);
    glutSpecialFunc(0);
    glutMouseFunc(0);
    glutMotionFunc(0);
    glutMouseWheelFunc(0);
}

WindowControl::~WindowControl() {
	glutDestroyWindow(hWin);
}

void WindowControl::setTitle(std::string t) {
	title = t;
	glutSetWindowTitle(title.c_str());
}

int WindowControl::newEvent(int id, unsigned int msec) {
	lastEventId++;
	// cuidado, isso pode ser perigoso,
	// mas atende ao propósito simples do atual TP
	// (provavelmente, nunca irá ocorrer na prática)
	if (lastEventId >= INT_MAX)
		lastEventId = 1;
	Event event;
	event.win = this;
	event.id = id;
	eventMap.insert(EventMap::value_type(lastEventId, event));
	glutTimerFunc(msec, WindowControl::cbTimer, lastEventId);
	return lastEventId;
}

void WindowControl::deleteEvent(int& eventId) {
	if (eventMap.erase(eventId))
		eventId = 0;
}

int WindowControl::getEventId(int eventId) {
	std::map<int, Event>::iterator it;
	it = eventMap.find(eventId);
	if (it != eventMap.end()) {
		return (*it).second.id;
	}
	return 0;
}

inline void WindowControl::calculateFPS()
{

    //  Increase frame count
    frameCount++;

    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    int currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = (frameCount * 1000) / timeInterval;

        //  Set time
        previousTime = currentTime;

        //  Reset frame count
        frameCount = 0;
    }
}
