//
//  main.cpp
//  OpenGLDemo
//
//  Created by Chang Liu on 8/16/16.
//  Copyright © 2016 Chang Liu. All rights reserved.
//


/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */



/*************************************************************
 * v1: build basic model and sphere outline
 *
 *
 **************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
GLUquadricObj *qobj;
float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = -1.0f;
float scale = 0.0f;


int win1;

int list = 1;





void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (glutGetWindow() == win1) {
		glCallList(list);   /* render sphere display list */
	} else {
		glCallList(1);      /* render sphere display list */
	}
    
	glutSwapBuffers();
}

void keyboard_s(unsigned char key, int x, int y)
{
    printf("trigger the keyboard, (%c,%d,%d)\n", key, x, y);
    switch (key)
    {
            case 'h' : ballX -= 0.05f;
                break;
            case 'l' : ballX  += 0.05f;
                break;
            case 'k' : ballY += 0.05f;
                break;
            case 'j' : ballY -= 0.05f;
                break;
            case 'r' : ballZ += 0.05f;
                break;
            case 'f' : ballZ -= 0.05f;
                break;
            case 'p': scale += 0.02;
                break;
            case 'q': scale -= 0.02;
                break;
            default:
                break;
    }
}
                 
                 
void display_win1(void)
{
	glPushMatrix();
    glTranslatef(ballX,ballY,ballZ);        //moving it toward the screen a bit on creation
    glScalef(1+scale,1+scale,1+scale); //scalede
	display();
	glPopMatrix();
}

void init(void)
{
	gluQuadricDrawStyle(qobj, GLU_FILL);
	glNewList(1, GL_COMPILE);  /* create sphere display list */
	gluSphere(qobj, /* radius */ 1.0, /* slices */ 20,  /* stacks

							     */ 20);
    glEndList();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glNewList(2, GL_COMPILE);  /* create sphere display list */
	gluSphere(qobj, /* radius */ 1.0, /* slices */ 20,  /* stacks

							     */ 20);
    glEndList();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ 1.0,
			/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
			0.0, 0.0, 0.0,      /* center is at (0,0,0) */
			0.0, 1.0, 0.);      /* up is in positive Y direction */
	glTranslatef(0.0, 0.0, -1.0);
}



void moveDisplay()
{
    glutPostRedisplay();                //标记当前窗口需要重绘，否则不会移动/伸缩
}


int main(int argc, char **argv)
{
	qobj = gluNewQuadric();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	win1 = glutCreateWindow("sphere");
	init();
	glutDisplayFunc(display_win1);
    glutKeyboardFunc(keyboard_s);
    glutIdleFunc(moveDisplay);

	glutMainLoop();
    glutFullScreen ();
	return 0;
}
