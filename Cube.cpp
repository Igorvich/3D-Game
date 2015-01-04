#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Cube.h"

using namespace std;

Cube::Cube()
{
}

Cube::Cube(int size, int posBotLeft[], GLuint textureSide, GLuint textureTop, GLuint textureBot, int idNumber)
{
	Cube::setId(idNumber);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureSide);

	glBegin(GL_QUADS);

	// front
	glTexCoord2f(0, 1);	glVertex3f(posBotLeft[0], posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 1);	glVertex3f(posBotLeft[0] + size, posBotLeft[1], posBotLeft[2]);
	glTexCoord2f(1, 0);	glVertex3f(posBotLeft[0] + size, posBotLeft[1] + size, posBotLeft[2]);
	glTexCoord2f(0, 0);	glVertex3f(posBotLeft[0], posBotLeft[1] + size, posBotLeft[2]);

	glEnd();

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

	glBindTexture(GL_TEXTURE_2D, textureTop);

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

Cube::~Cube()
{
}