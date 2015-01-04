#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Object.h"

using namespace std;

class ObjectHandler
{
private:

public:
	ObjectHandler();
	~ObjectHandler();
	void rotateObject(Object *object, int direction, int step);
	void moveObject(Object *object, int direction, int step);
	void createObject(int size, int positionBotLeft[], GLuint sideTexture, GLuint topTexture, GLuint botTexture);
	void createFloor(int length, int width, GLuint texture, int startPos[]);
	void createCube(int size, int positionBotLeft[], GLuint sideTexture, GLuint topTexture, GLuint botTexture);
	Object getObjectById(int id);
};