/*
 * Application.cpp
 *
 *  Created on: 06/06/2012
 *      Author: Frederico Sampaio
 */

#include <GL/glut.h>
#include "Application.h"

Application* Application::app = 0;

Application::~Application() {
	Application::app = 0;
}

Application* Application::getInstance() {
	if (!Application::app) {
		Application::app = new Application();
	}
	return Application::app;
}

Application::Application() {
	argc = 0;
	argv = 0;
}

void Application::setCmdParams(int argc, char** argv) {

}

void Application::init() {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
}

void Application::run() {
	glutMainLoop();
}

