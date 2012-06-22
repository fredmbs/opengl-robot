/*
 * WindowControl.h
 *
 *  Created on: 06/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

class WindowControl {
private:
	int hWin;
	int fps, frameCount, previousTime;
	std::string title;
	static void cbDisplay();
	static void cbReshape(int width, int height);
	static void cbKeyboard(unsigned char key, int x, int y);
	static void cbMouse(int button, int state, int x, int y);
	static void cbSpecialKeyboard(int key, int x, int y);
	static void cbMouseMove(int x, int y);
	static void cbMouseWheel(int wheel, int direction, int x, int y);
	static void cbTimer(int id);
	inline void calculateFPS();
protected:
	int  width, height;
	virtual void display() = 0;
	virtual void reshape(int width, int height) = 0;
	virtual void keyboard(unsigned char key, int x, int y) = 0;
	virtual void specialKey(int key, int x, int y) = 0;
	virtual void mouse(int button, int state, int x, int y) = 0;
	virtual void mouseMove(int x, int y) = 0;
	virtual void mouseWheel(int wheel, int direction, int x, int y) = 0;
	virtual unsigned int event(int id) = 0;
public:
	WindowControl();
	virtual ~WindowControl();
	void setTitle(std::string);
	virtual void configure() = 0;
	int newEvent(int, unsigned int);
	void deleteEvent(int&);
	int getEventId(int eventId);
	void enableEvents();
	void disableEvents();
	inline int getFps() { return fps; };
};

#endif /* WINDOW_H_ */
