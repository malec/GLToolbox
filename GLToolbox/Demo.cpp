//---------------------------------------
// Program: Homework 4 // GLToolbox
// Purpose: A set of tools for opengl
// Author:  Alexander Ahlbrandt
// Date:    March 2019
//---------------------------------------
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
	// Initialize OpenGL
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
	// Create OpenGL window
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Toolbox");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}