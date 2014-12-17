#pragma once
#include <string>
#include <stdio.h>
#include <glut.h>
#include <iostream>
#include <map>

using namespace std;

class Texture
{
private:
	const char* fileName;
	unsigned char* image;
	int width;
	int height;
	GLuint textureId;
	GLenum textureFiltering = GL_LINEAR;
public:
	Texture(const string);
	Texture(const string, GLenum);
	~Texture();
	GLuint getTextureId();
};