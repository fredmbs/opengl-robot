/*
 * Application.h
 *
 *  Created on: 06/06/2012
 *      Author: Frederico Sampaio
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "WindowControl.h"
#include <map>

class Application {
private:
	int argc;
	char** argv;
	static Application* app;
	Application();
public:
	virtual ~Application();
	static Application* getInstance();
	void setCmdParams(int, char**);
	void init();
	void run();
};

#endif /* APPLICATION_H_ */
