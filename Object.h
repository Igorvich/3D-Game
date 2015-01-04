#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"

using namespace std;

class Object
{
private:
	int size;
	int location[3];
	int id;
public:
	Object();
	Object(int size);
	///<summary>Method to create Object with size and beginning position.
	///The position array takes an X, Y and Z variable</summary>
	/// <para>int size, array position[X,Y,Z] </para>
	Object(int size, int positionBottomLeft[],
		GLuint textureSide, GLuint textureTop, 
		GLuint textureBot, int idNumber);
	~Object();
	Object getObject(void);
	void setLocation(int x, int y, int z);
	int *getLocation();
	void rotateObject(Object *object, int direction, int step);
	void moveObject(Object *object, int direction, int step);
	int getId();
	void setId(int number);
};