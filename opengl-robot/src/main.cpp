/*
 * main.cpp
 *
 */

#include <stdio.h>

#include "Application.h"
#include "RobotWindow.h"

int main(int argc, char **argv)
{
	// forçar saída imediata no console do eclipse
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Initialization stuff

	// Enter Glut Main Loop and wait for events
	Application* app = Application::getInstance();
	app->init();
	RobotWindow win(8, 0.2, 8);
	app->run();
	exit(0);
	return 0;
}

