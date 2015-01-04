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

	int i;
	int j;
	int counter = 0;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < length; j++)
		{
			counter++;
			//glLoadName(counter);
			glBegin(GL_QUADS);

			// bottom
			glTexCoord2f(0, 1);	glVertex3f(startPos[0] + i, startPos[1], startPos[2] + j);
			glTexCoord2f(1, 1);	glVertex3f(startPos[0] + 1 + i, startPos[1], startPos[2] + j);
			glTexCoord2f(1, 0);	glVertex3f(startPos[0] + 1 + i, startPos[1], startPos[2] + 1 + j);
			glTexCoord2f(0, 0);	glVertex3f(startPos[0] + i, startPos[1], startPos[2] + 1 + j);

			glEnd();
		}
		j = 0;
	}


	/*glBegin(GL_QUADS);

	// bottom
	glTexCoord2f(0, 1);	glVertex3f(startPos[0], startPos[1], startPos[2]);
	glTexCoord2f(1, 1);	glVertex3f(startPos[0] + width, startPos[1], startPos[2]);
	glTexCoord2f(1, 0);	glVertex3f(startPos[0] + width, startPos[1], startPos[2] + length);
	glTexCoord2f(0, 0);	glVertex3f(startPos[0], startPos[1], startPos[2] + length);

	glEnd();*/
}

Terrain::Terrain(int i, int j, int startPos[])
{
	glBegin(GL_QUADS);

	// bottom
	glTexCoord2f(0, 1);	glVertex3f(startPos[0] + i, startPos[1], startPos[2] + j);
	glTexCoord2f(1, 1);	glVertex3f(startPos[0] + 1 + i, startPos[1], startPos[2] + j);
	glTexCoord2f(1, 0);	glVertex3f(startPos[0] + 1 + i, startPos[1], startPos[2] + 1 + j);
	glTexCoord2f(0, 0);	glVertex3f(startPos[0] + i, startPos[1], startPos[2] + 1 + j);

	glEnd();
}

Terrain::Terrain(int numberOfTiles, GLuint texture, int startPos[])
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	int i;
	for (i = 0; i < numberOfTiles; i++)
	{
		glBegin(GL_QUADS);

		// bottom
		glTexCoord2f(0, 1);	glVertex3f(startPos[0] + i, startPos[1], startPos[2] + i);
		glTexCoord2f(1, 1);	glVertex3f(startPos[0] + 1 + i, startPos[1], startPos[2] + i);
		glTexCoord2f(1, 0);	glVertex3f(startPos[0] + 1 + i, startPos[1], startPos[2] + 1 + i);
		glTexCoord2f(0, 0);	glVertex3f(startPos[0] + i, startPos[1], startPos[2] + 1 + i);

		glEnd();
	}
}

Terrain::~Terrain()
{
}
