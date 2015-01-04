#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Object.h"
#include "ObjectHandler.h"
#include <vector>
#include "Terrain.h"
#include "Cube.h"

using namespace std;

vector<Object> objectList;

ObjectHandler::ObjectHandler()
{

}

ObjectHandler::~ObjectHandler()
{

}

void ObjectHandler::rotateObject(Object *object, int direction, int step)
{

}

void ObjectHandler::moveObject(Object *object, int direction, int step)
{

}
void ObjectHandler::createObject(int size, int positionBotLeft[], GLuint sideTexture, GLuint topTexture, GLuint botTexture)
{
	int temp = objectList.size() + 1;
	Object object = Object(size, positionBotLeft, sideTexture, topTexture, botTexture, temp);
	objectList.push_back(object);
}

void ObjectHandler::createCube(int size, int positionBotLeft[], GLuint sideTexture, GLuint topTexture, GLuint botTexture)
{
	Cube cube = Cube(size, positionBotLeft, sideTexture, topTexture, botTexture, 1);
	objectList.push_back(cube);
}

void ObjectHandler::createFloor(int length, int width, GLuint texture, int startPos[])
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
			glLoadName(counter);
			Terrain terrain = Terrain(i, j, startPos);
		}
	}
}

Object ObjectHandler::getObjectById(int id)
{
	int i;
	Object tempObject;
	for (i = 0; i < objectList.size(); i++)
	{
		if (objectList[i].getId() == id)
		{
			tempObject = objectList[i];
		}
	}
	return tempObject;
}
