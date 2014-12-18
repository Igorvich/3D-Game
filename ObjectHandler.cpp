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
