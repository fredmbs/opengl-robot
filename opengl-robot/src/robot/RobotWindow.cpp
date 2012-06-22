/*
 * RobotWindow.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Frederico Sampaio
 */

#include <iostream>
#include <stdlib.h>

#include <cmath>

#include "Maths.h"
#include "RobotWindow.h"

#define EVENT_START_FLY         1
#define EVENT_FLYING            2
#define EVENT_STOP_FLY          3
#define EVENT_TAKING_OFF        4
#define EVENT_LANDING           5
#define EVENT_RESET             6
#define EVENT_RESCUE            7
#define EVENT_SAFE_LANDING      8
#define EVENT_POST_REDISPLAY    9

#define FATOR_ROTACAO_MOUSE (180.0f/320)
#define DEFAUL_RADIUS       5
#define DEFAULT_LONGITUDE   0
#define DEFAULT_LATITUDE    35

#define MIN_CAM_RADIUS  2

///---------------------------------------------------------
	Color cinza(136, 136, 136);
	Color amarelo(217, 217, 0);
	Color cinzaEscuro(119, 119, 119);
	Color cinzaMaisEscuro(100, 100, 100);
	Color vermelho(255, 0, 0);
	Color verde(0, 255, 0);
	Color laranja(255, 165, 0);
	Color branco(255, 255, 255);
///----------------------------------------------------------

RobotWindow::RobotWindow(double x, double y, double z)
	: WindowControl(),
	  platform(x, y, z),
	  robot(5, platform),
	  textLives(), textGameOver(), textFps(),
	  borderland(8, 200),
	  platformColor()
{
	// registra os parêmtros da criação da classe
	platWidth = x;
	platHeight = y;
	platDeep = z;

	// cria e configura objetos para desenhar os textos
	textGameOver.setFontStyle(GLUT_BITMAP_TIMES_ROMAN_24);
	textGameOver.setText("GAME OVER");
	textGameOver.setPosition(-0.25, 0.1, -1);
	textGameOver.setColor(vermelho);
	textLives.setText("Vidas: %d", robot.getLives());
	textLives.setPosition(-0.95, 0.9, -1);
	textLives.setColor(verde);
	textFps.setText("FPS: %d", getFps());
	textFps.setPosition(-0.95, -0.95, -1);

	// agenda um evento para garantir ao menos um
	// glutPostRedisplay() por segundo
	newEvent(EVENT_POST_REDISPLAY, 1000);
	setFPS(120);

	// executa a configuração do ambiente openGL
	setTitle("TPCG - OpenGL");
	configure();

	// configura a posicição inicial da câmera
	robot.configureLookAt(lookAt);

	// agenda o evento de animação de iniciação do programa
	cameraRadius = 400;
	setCameraPosition(180, 90);
	newEvent(EVENT_RESET, interval);

	// inicia desenhando o limite espacial do jogo
	drawCage = true;

	// define as cores do robô
	platformColor.setColor(cinzaEscuro);
	robot.base.setColor(cinzaMaisEscuro);
	robot.armBase.setColor(amarelo);
	robot.arm.setColor(cinzaMaisEscuro);
	robot.claw.hand.setColor(amarelo);

	// configurações iniciais de controles do jogo
	mouseX = mouseY = 0;
	mouseButton = 0;
	mouseState = GLUT_UP;
	eventFlying = 0;

}

// destrutor padrão
RobotWindow::~RobotWindow() {
}

// desenha linhas representado os eixos no atual ponto (0,0,0)
void showAxis() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3f(00.0, 00.0, 00.0);
	glVertex3f(100.0, 00.0, 00.0);
	glColor3d(0, 1, 0);
	glVertex3f(00.0, 00.0, 00.0);
	glVertex3f(00.0, 100.0, 00.0);
	glColor3d(0, 0, 1);
	glVertex3f(00.0, 00.0, 00.0);
	glVertex3f(00.0, 00.0, 100.0);
	glEnd();
	glEnable(GL_LIGHTING);
    glPopMatrix();
}

void RobotWindow::configure()
{
	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// informações sobre a luz
	GLfloat luzAmbiente[4]={0.4, 0.4, 0.4, 1.0};
	GLfloat luzDifusa[4]={0.8, 0.8, 0.8, 1.0};    // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4]={4.0, 100, 4.0, 0};

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Capacidade de brilho do material
	GLfloat especularidade[4]={0.5,0.5,0.5,0.5};
	GLint especMaterial = 60;
	// Define a refletância do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	//
	GLfloat materialColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Habilita a definição da cor do material a partir da cor corrente
	// Usar as cores correntes para colorir os materiais perceptíveis no escuro
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING); // Declara iluminação
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0); // Usa iluminação na luz/lâmpada 0
	// Habilita o depth-buffering
	// Faz a luz preencher o buffer de pronfundidade e não só o fundo
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//glDepthRange(0.0f,1.0f);
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DITHER);


	//glEnable(GL_POINT_SMOOTH);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(0.5);

	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//glDepthFunc( GL_LEQUAL );
	//glClearAccum( 0.0, 0.0, 0.0, 0.0 );

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
	//glDepthFunc(GL_EQUAL);
	//glDepthFunc(GL_GEQUAL);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

// ajusta configuração de FPS por meio da variável que guarda o
// intervalo de tempo para a ativação dos eventos
void RobotWindow::setFPS(unsigned int fps) {
	interval = 1000/fps;
}

// trata o evento de redimensionamento da tela
void RobotWindow::reshape(int width, int height) {
	this->width = width;
	this->height = height;
    glViewport(0, 0,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)(width)/(float)(height), 0.01, 1000);
    glutPostRedisplay();
}

// inicia os valores padrão da posição da câmera
void RobotWindow::resetCamera() {
	cameraRadius = DEFAUL_RADIUS;
	setCameraPosition(DEFAULT_LONGITUDE, DEFAULT_LATITUDE);
	glutPostRedisplay();
}

// calcula a posição da câmera em funçãa do atual raio (distância até o robot)
// e das longitudes e latitudes especificadas
void RobotWindow::setCameraPosition(double lon, double lat) {
	cameraLongitude = fmod(lon, 360.0);
	cameraLatitude = fmod(lat, 360);
	double radiusLat = cos(cameraLatitude * (M_PI/180)) * cameraRadius;
	eye.x = sin(cameraLongitude * (M_PI/180)) * radiusLat + lookAt.x;
	eye.y = sin(cameraLatitude * (M_PI/180)) * cameraRadius + lookAt.y;
    eye.z = cos(cameraLongitude * (M_PI/180)) * radiusLat + lookAt.z;
}


/**
 * trata evento de teclados (ASCII)
 */
void RobotWindow::keyboard(unsigned char key, int x, int y) {
	switch(key) {
	// evento de reset da câmera e das posições iniciais
	case 'R':
	case 'r':
		newEvent(EVENT_RESET, interval);
		break;
	// evento de afastamento da câmera
	case 'v':
	case 'V':
		cameraRadius += 0.5;
		setCameraPosition(cameraLongitude, cameraLatitude);
		break;
	// evento de aproximação da câmera
	case 'f':
	case 'F':
		if (cameraRadius >= MIN_CAM_RADIUS) {
			cameraRadius -= 0.5;
			setCameraPosition(cameraLongitude, cameraLatitude);
		}
		break;
	// rotação da base do braço do robô
	case 'z':
	case 'Z':
		if (!robot.isFlying())
			robot.armBase.rotate(1);
		break;
	case 'c':
	case 'C':
		if (!robot.isFlying())
			robot.armBase.rotate(-1);
		break;
	// rotação do braço do robô
	case 'q':
	case 'Q':
		if (!robot.isFlying())
			robot.arm.rotate(1);
		break;
	case 'a':
	case 'A':
		if (!robot.isFlying())
			robot.arm.rotate(-1);
		break;
	// rotação da garra do robô (inclui toda a hélice e os dedos da garra)
	case 'e':
	case 'E':
		if (!robot.isFlying())
			robot.claw.rotate(1);
		break;
	case 'd':
	case 'D':
		if (!robot.isFlying())
			robot.claw.rotate(-1);
		break;
	// rotação dos dedos da garra
	case 'x':
	case 'X':
		robot.claw.finger.rotate(1);
		break;
	case 's':
	case 'S':
		robot.claw.finger.rotate(-1);
		break;
	// alterna estado do robô entre de voando, pousando sobre a base ou resgate
	case 't':
	case 'T':
		// se  o robô está voando
		if (robot.isFlying()) {
			// e já está tentando pousar
			if (getEventId(eventFlying) == EVENT_LANDING) {
				deleteEvent(eventFlying);
				// ativa o modo de resgate
				eventFlying = newEvent(EVENT_RESCUE, interval);
			} else {
				deleteEvent(eventFlying);
				// se está voando, ativa o modo de pouso
				eventFlying = newEvent(EVENT_LANDING, interval);
			}
		} else {
			// se não está voando, inicia o modo de "voando"
			robot.startFlying();
			deleteEvent(eventFlying);
			eventFlying = newEvent(EVENT_START_FLY, interval);
		}
		break;
	// faz uma animação de pouso do robô até sua posição inicial
	case 'y':
	case 'Y':
		if (robot.isFlying()) {
			if (getEventId(eventFlying) == EVENT_FLYING) {
				deleteEvent(eventFlying);
				eventFlying = newEvent(EVENT_SAFE_LANDING, interval);
			}
		}
		break;
	// sobe o robô, caso esteja flutuando (após as animações de início do voo)
	case 'g':
	case 'G':
		robot.moveUp();
		break;
	// desce o robô, caso esteja flutuando (após as animações de início do voo)
	case 'b':
	case 'B':
		robot.moveDown();
		break;
	// modifica o ângulo entre as garras (que formam a hélice)
	case 'i':
	case 'I':
		if (!robot.isFlying())
			robot.claw.rotateAngle(1);
		break;
	case 'k':
	case 'K':
		if (!robot.isFlying())
			robot.claw.rotateAngle(-1);
		break;
	// modifica o ângulo de cada garras (simulando o ângulo de ataque da hélice)
	case 'o':
	case 'O':
		if (!robot.isFlying())
			robot.claw.rotateAttack(0.25);
		break;
	case 'l':
	case 'L':
		if (!robot.isFlying())
			robot.claw.rotateAttack(-0.25);
		break;
	// liga/desliga o desenho da grade de limíte espacial do jogo
	case 'p':
	case 'P':
		drawCage = !drawCage;
		break;
	// modifica o ângulo de deslocamento (usado na rotação das hélices)
	case '+':
	case '=':
		robot.aceleratePropeller(1);
		break;
	case '-':
	case '_':
		robot.aceleratePropeller(-1);
		break;
	default:
		// se não for nenhuma das teclas de comando, retorna sem fazer nada
		return;

	}
	// agenda a renderização do próxim frame
	glutPostRedisplay();
}

/**
 * trata os eventos das teclas especiais
 */
void RobotWindow::specialKey(int key, int x, int y) {
	switch(key) {
	// faz a mudança de posição X e Y do robô
	case GLUT_KEY_LEFT: /* Seta para Cima */
		robot.moveBack();
		break;
	case GLUT_KEY_RIGHT: /* Seta para Baixo */
		robot.moveFront();
		break;
	case GLUT_KEY_DOWN: /* Seta para Cima */
		robot.moveRight();
		break;
	case GLUT_KEY_UP: /* Seta para Baixo */
		robot.moveLeft();
		break;
	default:
		return;

	}
	glutPostRedisplay();
}

/**
 * modifica os ângulos de rotação pela entrada de eventos de mouse (movimento)
 */
void RobotWindow::mouseMove(int x, int y) {
	if (mouseButton == GLUT_LEFT_BUTTON && mouseState == GLUT_DOWN) {
		float dx = x - mouseX;
		float dy = y - mouseY;
		cameraLongitude -= (dx * FATOR_ROTACAO_MOUSE);
		cameraLatitude += (dy * FATOR_ROTACAO_MOUSE);
		mouseX = x;
		mouseY = y;
		setCameraPosition(cameraLongitude, cameraLatitude);
		glutPostRedisplay();
	}
}

/**
 * trata os eventos da roda do mouse (equivalentes ao zoom dos pads)
 * aumentando ou diminuindo o raio que representa a distância entre o robô
 * e a câmera
 */
void RobotWindow::mouseWheel(int wheel, int direction, int x, int y) {
	cameraRadius -= direction * 0.2;
	if (cameraRadius < MIN_CAM_RADIUS) cameraRadius = MIN_CAM_RADIUS;
	setCameraPosition(cameraLongitude, cameraLatitude);
	glutPostRedisplay();
}

/**
 * trata os eventos de pressionamento dos botões do mouse
 */
void RobotWindow::mouse(int button, int state, int x, int y) {
	mouseButton = button;
	mouseState = state;
	if(button == GLUT_LEFT_BUTTON) {
		if(state == GLUT_DOWN) {
			mouseX = x;
			mouseY = y;
		} else if(state == GLUT_UP) {
		}
	} else if(button == GLUT_MIDDLE_BUTTON) {
		resetCamera();
	}
}

/**
 * realiza a renderização de um frame do jogo
 */
void RobotWindow::display() {

	// ajusta para a matriz de modelo e zera as transformações
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// obtém a posição do robô e ajusta câmera para apontar para essa direção
    robot.configureLookAt(lookAt);
    setCameraPosition(cameraLongitude, cameraLatitude);
    gluLookAt(eye.x, eye.y, eye.z, lookAt.x, lookAt.y, lookAt.z, 0.0, 1.0, 0.0);

    // limpa o atual buffer de renderização
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // verifica se o jogo terminou (o robo tem vidas?)
    if (robot.getLives() == 0) {
    	// desenha o Game Over e paralisa a aplicação
    	textGameOver.draw2D();
    	glutSwapBuffers();
    	disableEvents();
    	return;
    } else // senão existem vidas
    	// verifica se o robot deve ser revivido
    	if (!robot.isAlive()) {
    		robot.revive();
    		newEvent(EVENT_RESET, interval);
    	}

    // verifica se deve desenhar o limite espacial do jogo
    if (drawCage) {
    	//glPushMatrix();
    	borderland.draw();
    	//glPopMatrix();
    }

    // desenha a plataforma
    //glPushMatrix();
    glColor4dv(platformColor.getVect());
    platform.draw();
    //glPopMatrix();

    /*/ Desenha uma pequena esfera na posição lookAt para referência visual
    glPushMatrix();
    glTranslated(lookAt.x, lookAt.y, lookAt.z);
    glColor3dv(laranja.getVect());
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
	/*/

    // desenha o robô
    //glPushMatrix();
    robot.draw();
    //glPopMatrix();

    // desenha o número de vidas
    textLives.setText("Vidas: %d", robot.getLives());
    textLives.draw2D();

    // desenha o número de Frames Per Second
	textFps.setText("FPS: %d", getFps());
	textFps.draw2D();

	// solicita a saída em vídeo do quadro renderizado
    glutSwapBuffers();
}

/**
 * método de tratamento de evento do "timer"
 * são executados em resposta ao "glTimerFunc" (da super-classe Window)
 * recebe de entrada a identificação do evento (definido pela aplicação)
 * retorna o tempo (em milisegundos) para a próxima execução do evento
 * caso retorne o intervalo de retorno = 0, o evento não é reagendado (termina)
 * senão, o evento é reagendado "glTimerFunc" e será chamado novamente
 * depois de um tempo maior ou igual ao intervalo especificado
 * (não retorna número negativo)
 */
unsigned int RobotWindow::event(int id) {
	switch(id) {

	case EVENT_START_FLY:
		// evento que inicia a rotação das hélices (aceleração)
		// se estiver durante a animação do início, agenda o próximo frame
		if (robot.animateStartFlying()) {
			glutPostRedisplay();
			return interval;
		}
		// se está na base
		if (robot.isInBase())
			// decola
			eventFlying = newEvent(EVENT_TAKING_OFF, interval);
		else
			// senão, basta continuar o voo
			eventFlying = newEvent(EVENT_FLYING, interval);
		break;
	case EVENT_TAKING_OFF:
		// evento que faz a animação da subida depois do início do voo
		// se estiver animando a subida, agenda o próximo frame
		if (robot.animateTakingOff()) {
			glutPostRedisplay();
			return interval; // continua o evento
		}
		// se terminou a decolagem, inicia o evento de voo (flutação)
		eventFlying = newEvent(EVENT_FLYING, interval);
		break;
	case EVENT_FLYING:
		// se está animando o voo, agenda o próximo frame
		// rotação da hélice
		if (robot.animateFlying()) {
			glutPostRedisplay();
			return interval;
		}
		break;
	case EVENT_STOP_FLY:
		// evento que faz a redução da aceleração da hélice
		glutPostRedisplay();
		// se continua na parada do voo, continua o evento
		if (robot.animateStopFlying()) {
			return interval;
		}
		break;
	case EVENT_LANDING:
		// evento que faz a animação da queda do robô
		glutPostRedisplay();
		// se está fazendo a animação do puso, continua
		if (robot.animateLanding()) {
			return interval;
		}
		// senão, verifica se o robô está vivo
		if (robot.isAlive()) {
			// se estiver, inicia a animação de parada do voo
			// (desaceleração e reposicionamento)
			robot.stopFlying();
			eventFlying = newEvent(EVENT_STOP_FLY, interval);
		}
		break;
	case EVENT_RESCUE:
		// evento que anima o resgate do robô durante a queda
		glutPostRedisplay();
		// se a animação de resgate está ativa, continua o evento
		// (desaceleração da queda)
		if (robot.animateRescue()) {
			return interval;
		}
		// se continua vivo ao final do resgate
		if (robot.isAlive()) {
			// retorna a animação de voo (flutuação)
			eventFlying = newEvent(EVENT_FLYING, interval);
		}
		break;
	case EVENT_SAFE_LANDING:
		// evento faz a animação de um pouso seguro
		glutPostRedisplay();
		// se ainda está na animação do pouso, continua o evento
		if (robot.animateSafeLanding()) {
			return interval;
		}
		// senão, para o voo e inicia a animação de parada (desaceleração)
		robot.stopFlying();
		eventFlying = newEvent(EVENT_STOP_FLY, interval);
		break;
	case EVENT_RESET:
		// evento faz a animação do reset da câmera e do robô
		if (animateReset()) {
			glutPostRedisplay();
			return interval;
		}
		break;
	case EVENT_POST_REDISPLAY:
		// evento que garante ao menos um quadro a cada segundo
		// para atualizar o texto de FPS na tela
		glutPostRedisplay();
		return 1000;
	}
	// termina o atual evento em execução
	return 0;
}

bool RobotWindow::animateReset() {
	// definição empírica de uma desaceleração da queda
	double niceApproximation = (abs(cameraRadius - DEFAUL_RADIUS) / 20) + 0.3;
	// anima a reposição para o raio inicial
	bool action1 = approximate(cameraRadius, niceApproximation, DEFAUL_RADIUS);
	// anima a reposição para a longitude inicial
	bool action2 = circularApproximate(cameraLongitude, 1.5, DEFAULT_LONGITUDE);
	// anima a reposição para a latitude inicial
	bool action3 = circularApproximate(cameraLatitude, 1.5, DEFAULT_LATITUDE);
	// anima a reposição inicial das parte do robô
	bool action4 = robot.animateGoingInitialPosition();
	// se qualquer animação que afeta a câmera foi feita
	if (action1 || action2 || action3) {
		// ajusta a posição da câmera
		setCameraPosition(cameraLongitude, cameraLatitude);
	}
	// retorna indicando se ainda existe animação sendo feita
	return (action1 || action2 || action3 || action4);
}
