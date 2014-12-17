#include <stdio.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Terrain.h"
#include "Texture.h"

using namespace std;

Terrain::Terrain()
{

}

Terrain::Terrain(int length, int width, GLuint texture, int startPos[])
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	// bottom
	glTexCoord2f(0, 1);	glVertex3f(startPos[0], startPos[1], startPos[2]);
	glTexCoord2f(1, 1);	glVertex3f(startPos[0] + width, startPos[1], startPos[2]);
	glTexCoord2f(1, 0);	glVertex3f(startPos[0] + width, startPos[1], startPos[2] + length);
	glTexCoord2f(0, 0);	glVertex3f(startPos[0], startPos[1], startPos[2] + length);

	glEnd();
}

Terrain::~Terrain()
{
}
