#pragma once
#include <stdio.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace std;

class Camera
{
private:
	float cameraYaw, cameraPitch;
	float eyeX, eyeY, eyeZ;
	float centerX, centerY, centerZ;
	float upX = 0.0, upY = 1.0, upZ = 0.0;
	bool isMoving = false;
public:
	Camera();
	~Camera();

	void init();
	void update();
	void getPos();
	void setPosition(float x, float y, float z);
};