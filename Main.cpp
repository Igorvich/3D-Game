#pragma once
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"
#include "Cube.h"
#include "Terrain.h"

Texture minecraftTexture{ "Resources/dirtSide.png" };
Texture dirtTopTexture{ "Resources/dirtTop.png" };
Texture dirtBottomTexture{ "Resources/dirtBottom.png" };
Texture landscape{ "Resources/landscape.jpg" };

GLuint blockTexture;
GLuint dirtTopTextr;
GLuint dirtBotTexture;
GLuint landscapeTexture;

float cameraX = 0.0, cameraY = 0.0, cameraZ = -10.0, cameraWidth = 1024, cameraHeight = 768, angle = 0;
float rotateX = 0.0, rotateY = -100.0, rotateZ = 0.0;
float centerX = 512, centerY = 384;
float angleX = 0, angleY = 0, angleZ = 0;
float zFar = 15000, zNear = 0.00001;
float zoomCamera = 0, zoomX = 0, zoomY = 0;
bool horizontal = false, vertical = false;

int oldX, oldY;
bool rotateArea = false;
float theta = -1.569999, phi = 0;
float eyeX = 0.000797, eyeY, eyeZ, pickObjX, pickObjY, pickObjZ;

void setCameraPosition(void);
void rotateCamera(void);
void drawCube();
void resetCamera(void);


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	GLfloat LightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);

	GLfloat LightModelAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat MaterialSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat MaterialEmission[] = { 0, 0, 0, 1.0f };
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
	drawCube();
	
	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, width / height, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
}

void MouseButton(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:			// Middle mouse button
		rotateArea = false;
		if (state == GLUT_DOWN)
		{
			printf("Right Click At %d %d \n", x, y);
			oldX = x;
			oldY = y;
			rotateArea = true;
			pickObjX = 0;
			pickObjY = 0;
			pickObjZ = 0;
			printf("The value from theta is: %f/n", theta);
			printf("The value from eyeX is: %f/n", eyeX);
		}
		else if (state == GLUT_DOWN)
			rotateArea = false;
		printf("Middle Click At %d %d \n", x, y);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		printf("Left Click At %d %d \n", x, y);
		break;
	case GLUT_WHEEL_UP:
		printf("Scroll Up At %d %d\n", x, y);
		zoomCamera -= 0.2;
		//zoomX = (x - glutGet(GLUT_WINDOW_WIDTH) / 2) /10;
		//zoomY = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2)/10;
		break;
	case GLUT_WHEEL_DOWN:
		printf("Scroll Down At %d %d\n", x ,y);
		zoomCamera += 0.2;
		//zoomX = (x - glutGet(GLUT_WINDOW_WIDTH)/2)/10;
		//zoomY = (y - glutGet(GLUT_WINDOW_HEIGHT) / 2) / 10;
		printf("The width of the screen is: %d\n", glutGet(GLUT_WINDOW_WIDTH));
		break;
	}
	setCameraPosition();
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
		case 119:		// W key
			cameraY += 5.0;
			//vertical = true;
			//horizontal = false;
			//rotateY += 2.5;
			//angle += 2.5;
			break;
		case 97:		// A key
			cameraX -= 5.0;
			//horizontal = true;
			//vertical = false;
			//rotateX -= 2.5;
			//angle -= 2.5;
			break;
		case 115:		// S key
			cameraY -= 5.0;
			//vertical = true;
			//horizontal = false;
			//rotateY -= 2.5;
			//angle -= 2.5;
			break;
		case 100:		// D key
			cameraX += 5.0;
			//horizontal = true;
			//vertical = false;
			//rotateX += 2.5;
			//angle += 2.5;
			break;
		case 113:		// Q key
			angleX-=5;
			break;
		case 101:		// E key
			angleX+=5;
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
	setCameraPosition();
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

void drawCube(int size, int leftBottomLocation)
{
	
}

void drawCube()
{
	blockTexture = minecraftTexture.getTextureId();
	dirtTopTextr = dirtTopTexture.getTextureId();
	dirtBotTexture = dirtBottomTexture.getTextureId();
	landscapeTexture = landscape.getTextureId();
	/*glBindTexture(GL_TEXTURE_2D, blockTexture);
	glEnable(GL_TEXTURE_2D);
	*/
	glPushMatrix();

	glTranslatef(-0.5, -0.5, 0);

	glTranslatef(zoomX, zoomY, zoomCamera);

	glTranslatef(0.5, 0.5, 0.5);

	/*if (vertical)
		glRotatef(angle, rotateX, rotateY, 0);
		if (horizontal)
		glRotatef(angle, rotateX, rotateY, 0);
		*/
	//glRotatef(angle, rotateX, rotateY, rotateZ);


	glRotatef(angleX, 0, 1, 0);
	glRotatef(angleY, 1, 0, 0);
	glRotatef(angleZ, 0, 0, 1);
	
	glTranslatef(-0.5, -0.5, -0.5);

	int position[] = { 0, 0, 0 };
	int position1[] = { 4, 0, 0 };
	Cube cube = Cube(1, position, blockTexture, dirtTopTextr, dirtBotTexture);
	//Cube cube1 = Cube(2, position1, blockTexture, dirtTopTextr, dirtBotTexture);
	//Cube cube2 = Cube(10, position, blockTexture, dirtTopTextr, dirtBotTexture);

	Terrain terrain = Terrain(10, 6, landscapeTexture, position);

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