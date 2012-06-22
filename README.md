opengl-robot
============

Graphic Computer : Robot Simulator
----------------------------------

### Introduction

This is a simple OpenGL application to simulate a robot (mechanic arm) that can fly rotating it's claws. This is a college work of Graphic Computer discipline, orientated by professor Moisés Henrique Ramos Pereira (<moiseshrp@gmail.com>).

The main goal of this software is to experiment and demosntrate the OpenGL resources, specialy the basics ones.

### Install

  The software is written in C++ and, besides OpenGL, it uses GLU and GLUT (freeglut) library. 

  I used Eclipse Indigo C++ with MinGW in Windows 7. 
  But, the software was designed to be cross-platform (as possible) and was tested in differents SO and compilers.

  The "compile.sh", taken form console output of eclipse "build project" command, 
  is a batch file intented to easily generate the executable in Linux shell (if don't fail :)
  Obviously, you need to grant permission to execute the file (chmod +x compile.sh).
  if it works, a executable binary file, named "opengl-robot", will be created at the same directory.

### How to use

The simulator uses keyboard to trigger robot actions and mouse to change the camera perspective.

- General commands
  - Arrows keys right or left: Moving robot along X axis
  - Arrows keys up or down: Moving robot along X axis
  - "F" or mouse wheel: Approaching the camera (ZOON IN) 
  - "V" or mouse wheel: Take away the camera (ZOON OUT) 
  - Move mouse with right button pressed: Rotate the camera 
  - "P": Toggle (on/off) the grid boundary

- Mode "on the platform" commands
  - "R": Reposition the robotic arm and camera (RESET)
  - "H": Start "flying" mode
  - "C" or "Z": Rotate the arm base at Z axis
  - "S" or "X": Open/close the claw
  - "A" or "Q": Rotate the arm (set)
  - "E" or "D": Rotate the hand (propeller) 
  - "I" or "K": Open/close the angle between the blades (hand parts) 
  - "O" or "L": Increasing/decrease attack angle of blades (hand parts)
 
- Mode "flying" commands
  - "R": Reposition the camera (RESET)
  - "T": Toggle (on/off) the propellers rotation (RESCUE)
  - "G" or "B": Get up/down the robot
  - "+" or "-": Increase/decrease propeller acceleration 
  - "Y": Safe landing at platform

### Tests

The software was tested in those environments:

- Windows 7 Professional 32bits
  - Eclipse IDE for C/C++ Developers Version: Indigo Service Release 2 Build id: 20120216-1857
  - MinGW com gcc (GCC) 4.6.2
    - freeglut 2.8.0 (para Windows 32bits)
  - Microsoft Visual Studio 2010 Version 10.0.40219.1 SP1Rel (Microsoft Visual C++ 2010   01021-532-2002102-70626)
    - freeglut 2.8.0 MSVC (para Windows 32bits)

- Ubuntu 11.10 (x86) (Linux version 3.0.0-17-generic)
  - g++ (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1
  - libqt4-opengl/oneiric-updates uptodate 4:4.7.4-0ubuntu8.1
  - libglu1-mesa/oneiric-updates uptodate 7.11-0ubuntu3.2
  - freeglut3/oneiric uptodate 2.6.0-1ubuntu2

- OpenSUSE 12.1 (x86_64)
  - g++ 4.6.1
  - opengl/glu
  - freeglut 
  
### AUTHORS
> ###### Frederico Martins Biber Sampaio <fredmbs@gmail.com>
> ###### Cristiano Madeira <cristianomad@gmail.com>