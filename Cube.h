#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"

using namespace std;

class Cube
{
private:
	int size;
	int location[3];
public:
	Cube(int size);
	///<summary>Method to create Cube with size and beginning position.
	///The position array takes an X, Y and Z variable</summary>
	/// <para>int size, array position[X,Y,Z] </para>
	Cube(int size, int positionBottomLeft[], GLuint textureSide, GLuint textureTop, GLuint textureBot);
	~Cube();
	Cube getCube(void);
	void setLocation(int x, int y, int z);
	int *getLocation();
	void rotateCube(Cube *cube, int direction, int step);
	void moveCube(Cube *cube, int direction, int step);
};