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

class Cube : public Object
{
private:
public:
	Cube();
	Cube(int size, int posBotLeft[], GLuint textureSide, GLuint textureTop, GLuint textureBot, int idNumber);
	~Cube();
};