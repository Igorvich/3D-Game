#pragma once
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"
#include "Object.h"
#include "Terrain.h"
#include "ObjectHandler.h"
#include <vector>
#include <algorithm>
#include "Main.h"

Texture minecraftTexture{ "Resources/dirtSide.png" };
Texture dirtTopTexture{ "Resources/dirtTop.png" };
Texture dirtBottomTexture{ "Resources/dirtBottom.png" };
Texture landscape{ "Resources/grass4.jpg" };
Texture viewScape{ "Resources/view.jpg" };

GLuint blockTexture;
GLuint dirtTopTextr;
GLuint dirtBotTexture;
GLuint landscapeTexture;
GLuint sideScapeTexture;

ObjectHandler objHandler;

float cameraX = 0.0, cameraY = 0.0, cameraZ = 0.0, cameraWidth = 1024, cameraHeight = 768, angle = 0;
float rotateX = 0.0, rotateY = -100.0, rotateZ = 0.0;
float centerX = 512, centerY = 384;
float angleX = 0, angleY = 0, angleZ = 0;
float zFar = 1024, zNear = 0.01;
float zoomCamera = 55.2, zoomX = 0, zoomY = 0;
float xLocation = 0, zLocation = 0;
bool horizontal = false, vertical = false;
int rotationState = 0;

int oldX, oldY;
bool rotateArea = false;
float theta = -1.569999, phi = 0;
float eyeX = 0.000797, eyeY, eyeZ, pickObjX, pickObjY, pickObjZ;

int selected = 0;

void setCameraPosition(void);
void rotateCamera(void);
void drawObject();
void drawSurrounding();
void resetCamera(void);


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	eyeX = 1*cos(theta);
	eyeY = 0;//pickObjY + 1*sin(phi)*sin(theta);
	eyeZ = 1*sin(theta);

	gluLookAt(	eyeX, eyeY, eyeZ,	// eye
				(-cos(theta)), 0, (-sin(theta)),	// center
				0, 1, 0);	// up

	// Lightinh
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	*/
	GLfloat LightPosition[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightAmbient[] = { 1.2f, 1.2f, 1.2f, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);

	GLfloat LightModelAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat MaterialSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat MaterialEmission[] = { 0.5, 0.5, 0.5, 1.0f };
	glLightModelfv(GL_AMBIENT, LightModelAmbient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, MaterialEmission);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/*GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	GLfloat lightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	GLfloat lightPosition[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	*/
	drawObject();
	//drawSurrounding();
	
	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, width / height, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
}

void list_hits(GLint hits, GLuint *names)
{
	int i;

	/*
	For each hit in the buffer are allocated 4 bytes:
	1. Number of hits selected (always one,
	beacuse when we draw each object
	we use glLoadName, so we replace the
	prevous name in the stack)
	2. Min Z
	3. Max Z
	4. Name of the hit (glLoadName)
	*/

	printf("%d hits:\n", hits);

	for (i = 0; i < hits; i++)
		printf("Number: %d\n"
		"Min Z: %d\n"
		"Max Z: %d\n"
		"Name on stack: %d\n",
		(GLubyte)names[i * 4],
		(GLubyte)names[i * 4 + 1],
		(GLubyte)names[i * 4 + 2],
		(GLubyte)names[i * 4 + 3]
		);

	printf("\n");

	if ((GLubyte)names[0 * 4 + 3] == 1)
	{
		printf("De ondergrond is geselecteerd!\n");
	}
}

void gl_select(int x, int y)
{
	GLuint buff[64] = { 0 };
	GLint hits, view[4];

	/*
	This choose the buffer where store the values for the selection data
	*/
	glSelectBuffer(64, buff);

	/*
	This retrieve info about the viewport
	*/
	glGetIntegerv(GL_VIEWPORT, view);

	/*
	Switching in selecton mode
	*/
	glRenderMode(GL_SELECT);

	/*
	Clearing the name's stack
	This stack contains all the info about the objects
	*/
	glInitNames();

	/*
	Now fill the stack with one element (or glLoadName will generate an error)
	*/
	glPushName(0);

	/*
	Now modify the vieving volume, restricting selection area around the cursor
	*/
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	/*
	restrict the draw to an area around the cursor
	*/
	gluPickMatrix(x, y, 1.0, 1.0, view);
	gluPerspective(90, 1024/768, zNear, zFar);

	/*
	Draw the objects onto the screen
	*/
	glMatrixMode(GL_MODELVIEW);

	/*
	draw only the names in the stack, and fill the array
	*/
	glutSwapBuffers();
	Display();

	/*
	Do you remeber? We do pushMatrix in PROJECTION mode
	*/
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	/*
	get number of objects drawed in that area
	and return to render mode
	*/
	hits = glRenderMode(GL_RENDER);

	/*
	Print a list of the objects
	*/
	list_hits(hits, buff);

	/*
	uncomment this to show the whole buffer
	* /
	gl_selall(hits, buff);
	*/

	glMatrixMode(GL_MODELVIEW);
}

void mousedw(int x, int y, int but)
{
	printf("Mouse button %d pressed at %d %d\n", but, x, y);
	gl_select(x, 768 - y); //Important: gl (0,0) ist bottom left but window coords (0,0) are top left so we have to change this!
}

void MouseButton(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			mousedw(x, y, button);
		}
		break;
	case GLUT_MIDDLE_BUTTON:			// Middle mouse button
		rotateArea = false;
		if (state == GLUT_DOWN)
		{
			printf("Middle Click At %d %d \n", x, y);
			oldX = x;
			oldY = y;
			rotateArea = true;
			pickObjX = 0;
			pickObjY = 0;
			pickObjZ = 0;
			printf("The value from theta is: %f\n", theta);
			printf("The value from eyeX is: %f\n", eyeX);
		}
		else if (state == GLUT_UP)
			rotateArea = false;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		printf("Left Click At %d %d \n", x, y);
		break;
	case GLUT_WHEEL_UP:
		printf("Scroll Up At %d %d\n", x, y);
		zoomCamera -= 2.0;
		//zoomX = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) /10;
		//zoomY = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2)/10;
		printf("The amount of zoom is: %f\n", zoomCamera);
		break;
	case GLUT_WHEEL_DOWN:
		printf("Scroll Down At %d %d\n", x ,y);
		zoomCamera += 2.0;
		//zoomX = (x - glutGet(GLUT_WINDOW_WIDTH)/2)/10;
		//zoomY = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2) / 10;
		printf("The width of the screen is: %d\n", glutGet(GLUT_WINDOW_WIDTH));
		printf("The amount of zoom is: %f\n", zoomCamera);
		break;
	}
	//setCameraPosition();
}

void MouseMotion(int x, int y)
{
	if (rotateArea)
	{
		theta += (x - oldX)*0.005f;
		phi += (y - oldY)*0.005f;
	}
	oldX = x;
	oldY = y;
}

void IdleFunc(void)
{
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
		{
		case 27:		// Escape key
			exit(0);
			break;
		case 120:		// X key
			if (rotationState < 3)
				rotationState++;
			else if (rotationState >= 3)
				rotationState = 0;
			break;
		case 119:		// W key
			cameraY -= 1;
			zoomCamera -= 1;
			//vertical = true;
			//horizontal = false;
			//rotateY += 2.5;
			//angle += 2.5;
			break;
		case 97:		// A key
			cameraX += 1;
			xLocation -= 1;
			//zLocation -= 1;
			//horizontal = true;
			//vertical = false;
			//rotateX -= 2.5;
			//angle -= 2.5;
			break;
		case 115:		// S key
			cameraY += 1;
			zoomCamera += 1;
			//vertical = true;
			//horizontal = false;
			//rotateY -= 2.5;
			//angle -= 2.5;
			break;
		case 100:		// D key
			cameraX -= 1;
			xLocation += 1;
			printf("The Xlocation is: %f\n", xLocation);
			//zLocation += 1;
			//horizontal = true;
			//vertical = false;
			//rotateX += 2.5;
			//angle += 2.5;
			break;
		case 113:		// Q key
			angleX-=5;
			printf("The X angle is: %f\n", angleX);
			break;
		case 101:		// E key
			angleX+=5;
			printf("The X angle is: %f\n", angleX);
			break;
		case 114:		// R key
			angleY +=5;
			break;
		case 116:		// T key
			angleY -=5;
			break;
		case 102:		// F key
			angleZ += 5;
			break;
		case 103:		// G key
			angleZ -= 5;
			break;
		case 122:		// Z key
			resetCamera();
			break;
			//114 = R
				//116 = T
		}
	//setCameraPosition();
}

void resetCamera()
{
	angleX = 0;
	angleY = 0;
	angleZ = 0;
}

void setCameraPosition()
{
	glViewport(cameraX, cameraY, cameraWidth, cameraHeight);
}

void rotateCamera()
{
}

void drawObject(int size, int leftBottomLocation)
{
	
}

void drawSurrounding()
{
	glPushMatrix();

	glBegin(GL_QUADS);

	glVertex3f(-20, 0, -40);
	glVertex3f(-20, 0, 20);
	glVertex3f(-20, 20, 20);
	glVertex3f(-20, 20, -20);

	glEnd();

	glPopMatrix();
}

void drawObject()
{
	blockTexture = minecraftTexture.getTextureId();
	dirtTopTextr = dirtTopTexture.getTextureId();
	dirtBotTexture = dirtBottomTexture.getTextureId();
	landscapeTexture = landscape.getTextureId();
	sideScapeTexture = viewScape.getTextureId();
	/*glBindTexture(GL_TEXTURE_2D, blockTexture);
	glEnable(GL_TEXTURE_2D);
	*/
	glPushMatrix();

	//glTranslatef(0, -0.5, 0);

	glTranslatef(-0, 0.5, 0);

	//glTranslatef(zoomX, zoomY, zoomCamera);
	glTranslatef(cameraX, cameraY, zoomCamera);

	glTranslatef(0, -0.5, 0);

	/*if (vertical)
		glRotatef(angle, rotateX, rotateY, 0);
		if (horizontal)
		glRotatef(angle, rotateX, rotateY, 0);
		*/
	//glRotatef(angle, rotateX, rotateY, rotateZ);
	
	//glTranslatef(-cameraX, 0, 0);

	switch (rotationState)
	{
	case 0:
		glRotatef(0, 0, 1, 0);
		glRotatef(-45, 1, 0, 0);
		break;
	case 1:
		glRotatef(-90, 0, 1, 0);
		glRotatef(45, 0, 0, 1);
		break;
	case 2:
		glRotatef(-180, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		break;
	case 3:
		glRotatef(-270, 0, 1, 0);
		glRotatef(-45, 0, 0, 1);
		break;
	}

	glRotatef(angleX, 0, 1, 0);
	glRotatef(angleY, 1, 0, 0);
	glRotatef(angleZ, 0, 0, 1);
	
	//glTranslatef(cameraX, 0, 0);

	int position[] = { -100, 0, -100 };
	int position1[] = { 50, 0, 0 };

	objHandler.createFloor(200, 200, landscapeTexture, position);

	glLoadName(1);

	objHandler.createCube(1, position1, blockTexture, dirtTopTextr, dirtBotTexture);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, sideScapeTexture);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);		glVertex3f(100, 40, -100);
	glTexCoord2f(0, 1);		glVertex3f(100, 0, -100);
	glTexCoord2f(0.25, 1);	glVertex3f(-100, 0, -100);
	glTexCoord2f(0.25, 0);	glVertex3f(-100, 40, -100);

	glTexCoord2f(0.25, 0);	glVertex3f(-100, 40, -100);
	glTexCoord2f(0.25, 1);	glVertex3f(-100, 0, -100);
	glTexCoord2f(0.5, 1);	glVertex3f(-100, 0, 100);
	glTexCoord2f(0.5, 0);	glVertex3f(-100, 40, 100);

	glTexCoord2f(0.5, 0);	glVertex3f(-100, 40, 100);
	glTexCoord2f(0.5, 1);	glVertex3f(-100, 0, 100);
	glTexCoord2f(0.75, 1);	glVertex3f(100, 0, 100);
	glTexCoord2f(0.75, 0);	glVertex3f(100, 40, 100);

	glTexCoord2f(0.75, 0);	glVertex3f(100, 40, 100);
	glTexCoord2f(0.75, 1);	glVertex3f(100, 0, 100);
	glTexCoord2f(1, 1);		glVertex3f(100, 0, -100);
	glTexCoord2f(1, 0);		glVertex3f(100, 40, -100);

	glEnd();

	//Object Object = Object(1, position, blockTexture, dirtTopTextr, dirtBotTexture);
	//Object Object1 = Object(2, position1, blockTexture, dirtTopTextr, dirtBotTexture);
	//Object Object2 = Object(10, position, blockTexture, dirtTopTextr, dirtBotTexture);

	/*glBegin(GL_QUADS);
	// Front side
	//glColor3f(1, 0, 0);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 1, 0);

	// Right side
	//glColor3f(0, 1, 0);
	glTexCoord2f(0, 1); glVertex3f(1, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(1, 1, 0);

	// Back side
	//glColor3f(0, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(1, 0, 1);
	glTexCoord2f(1, 1); glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0); glVertex3f(0, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(1, 1, 1);

	// Left side
	//glColor3f(1, 1, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 1);
	glTexCoord2f(1, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 1, 1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, dirtTopTextr);

	glBegin(GL_QUADS);
	// Top side
	//glColor3f(0, 1, 1);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(0, 1, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(0, 1, 1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, dirtBotTexture);

	glBegin(GL_QUADS);
	// Bottom side
	//glColor3f(1, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(1, 0, 1);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 1);

	glEnd();*/

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLUT example");
	// Initialize OpenGL graphics state
	InitGraphics();

	//Lighting
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	// Register callbacks:
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(IdleFunc);
	// Turn the flow of control over to GLUT
	glutMainLoop();
	return 0;
}