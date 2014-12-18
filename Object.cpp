#include <stdio.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Object.h"
#include "Texture.h"

using namespace std;

Object::Object()
{

}

Object::Object(int size)
{
	
}

Object::Object(int size, int posBotLeft[], GLuint textureSide, GLuint textureTop, GLuint textureBot, int idNumber)
{
	id = idNumber;
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	// front
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2]);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2]);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureSide);

	glBegin(GL_QUADS);

	// right
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2] + size);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2] + size);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2]);

	// back
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2] + size);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2] + size);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2] + size);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2] + size);

	// left
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2] + size);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2]);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2] + size);

	glEnd();

	glBindTexture(GL_TEXTURE_2D ,textureTop);

	glBegin(GL_QUADS);

	// top
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2]);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2]);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2] + size);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2] + size);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureBot);

	glBegin(GL_QUADS);

	// bottom
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2] + size);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2] + size);
	
	glEnd();
}

void Object::moveObject(Object *object, int direction, int step)
{

}

int Object::getId()
{
	return id;
}

Object Object::getObject()
{
	return NULL;
}

Object::~Object()
{}
