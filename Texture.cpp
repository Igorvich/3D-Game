#include <stdio.h>
#include <glut.h>
#include <string>
#include <iostream>
#include <map>
#include "Texture.h"
#include "stb_image.h"

using namespace std;

Texture::Texture(const string file)
{
	fileName = file.c_str();
	stbi_uc* img = stbi_load(fileName, &width, &height, NULL, 4);
	image = img;
	textureId = 0;
	//stbi_image_free(img);
	cout << "> " << fileName << " loaded" << endl;
}

Texture::Texture(const string file, const GLenum textFilter)
{
	fileName = file.c_str();
	textureFiltering = textFilter;
	stbi_uc* img = stbi_load(fileName, &width, &height, NULL, 4);
	image = img;
	textureId = 0;
	//stbi_image_free(img);
	cout << "> " << fileName << " loaded" << endl;
}

Texture::~Texture()
{
}

GLuint Texture::getTextureId()
{
	if (textureId == 0)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,
			0,					// level
			GL_RGBA,			// internal format
			width,				// width
			height,				// height
			0,					// border
			GL_RGBA,			// data format
			GL_UNSIGNED_BYTE,	// data type
			image);				// data
	}
	return textureId;
}