#include <glut.h>
#include <gl/GL.h>
#include "Texture.h"

class Main{
public:
	void setCameraPosition(void);
	void rotateCamera(void);
	void drawObject();
	void resetCamera(void);
	void Reshape(GLint, GLint);
	void Display(void);
};

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);
};

class Vec4f
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};
	Vec4f();
	Vec4f(Vec4f &other);
	Vec4f(float x, float y, float z, float w);
	float& operator [](int);
};
