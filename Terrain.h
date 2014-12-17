#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"

using namespace std;

class Terrain
{
private:
	int lengt, width, area;
public:
	Terrain();
	Terrain(int lenght, int width, GLuint texture, int startPos[]);
	~Terrain();
	Terrain getTerrain(void);
};