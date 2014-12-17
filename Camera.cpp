#include <stdio.h>
#include <math.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Camera.h"

using namespace std;

void Camera::init()
{
	/*cameraYaw = 0.0;
	cameraPitch = 0.0;
	Camera::setPosition(0.0, 0.0, 0.0);*/
}

void Camera::update()
{


	eyeX = cos(cameraYaw)*cos(cameraPitch);
	eyeY = sin(cameraPitch);
	eyeZ = sin(cameraYaw)*cos(cameraPitch);

	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

}

Camera::~Camera()
{}