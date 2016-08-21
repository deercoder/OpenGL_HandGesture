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
 * v2: finish the main body of controling shape/location
 * v3: major fix, change scales, color, shadow, reshape/rescaling.
 **************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <time.h>



#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];


GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

// default color, randomly changed when pressed `c`
GLfloat qaDefault[] = {0.8, 0.8, 0.8, 1.0};

GLUquadricObj *qobj;
float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = -1.0f;
float scale = 0.0f;

int win1;
int list = 1;


static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;



void makeStripeImage(void)
{
    int j;
    
    for (j = 0; j < stripeImageWidth; j++) {
        stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
        stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
        stripeImage[4*j+2] = (GLubyte) 0;
        stripeImage[4*j+3] = (GLubyte) 255;
    }
}


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

void set_random_color()
{
    srand(time(NULL));
    int r1 = rand() % 255;
    int r2 = rand() % 255;
    int r3 = rand() % 255;
    
    printf("random RGB color is :(%d, %d, %d)\n", r1, r2, r3);
    
    // scaling to the [0,1] division
    qaDefault[0] = r1 / 255.0f;
    qaDefault[1] = r2 / 255.0f;
    qaDefault[2] = r3 / 255.0f;
}


void keyboard_s(unsigned char key, int x, int y)
{
    printf("trigger the keyboard, (%c,%d,%d)\n", key, x, y);
    switch (key)
    {
        case 'h' :
            ballX -= 0.4f;
            roangles += 15.0f;
            break;
        case 'l' :
            ballX  += 0.4f;
            roangles -= 15.0f;
            break;
        case 'k' :
            ballY += 0.4f;
            roangles += 15.0f;
            break;
        case 'j' :
            ballY -= 0.4f;
            roangles -= 15.0f;
            break;
        case 'r' : ballZ += 0.8f;
            break;
        case 'f' : ballZ -= 0.8f;
            break;
        case 'p': scale += 1.5f;
            break;
        case 'q': scale -= 0.5f;
            break;
        case 'c': set_random_color();
            break;
        default:
            break;
    }
}


void display_win1(void)
{

    for (int i = 0; i < 8; i++) {
        glPushMatrix();

        glTranslatef(ballX, ballY, ballZ);    //moving it toward the screen a bit on creation
        glScalef(1+scale,1+scale,1+scale); //scaled
        glRotatef(roangles, 0.0, 0.0, 1.0);
        display();

        glPopMatrix();
    }

    
    // set the color of the sphere, color is defined by qaDefault
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaDefault);
}

void init(void)
{
    gluQuadricDrawStyle(qobj, GLU_FILL);
    glNewList(1, GL_COMPILE);  /* create sphere display list */
    gluSphere(qobj, /* radius */ 0.3, /* slices */ 100,  /* stacks*/ 100);
    glEndList();
    
    /// start the texture
    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    glTexGenfv(GL_S, currentPlane, currentCoeff);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_1D);
    
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE);
    glEnable(GL_COLOR);
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
    
    roangles = 45.0f;
}



void moveDisplay()
{
    glutPostRedisplay();   //标记当前窗口需要重绘，否则不会移动/伸缩
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}


int main(int argc, char **argv)
{
    qobj = gluNewQuadric();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    win1 = glutCreateWindow("sphere");
    init();
    glutDisplayFunc(display_win1);
    glutKeyboardFunc(keyboard_s);
    glutIdleFunc(moveDisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    glutFullScreen();
    return 0;
}
