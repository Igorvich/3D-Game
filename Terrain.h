#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"
#include "Object.h"

using namespace std;

class Terrain : public Object
{
private:
	int lengt, width, area;
public:
	Terrain();
	Terrain(int i, int j, int startPos[]);
	Terrain(int lenght, int width, GLuint texture, int startPos[]);
	Terrain(int numberOfTiles, GLuint texture, int startPos[]);
	~Terrain();
	Terrain getTerrain(void);
};