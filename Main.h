#include <glut.h>
#include <gl/GL.h>
#include "Texture.h"

class Main{
public:
	void setCameraPosition(void);
	void rotateCamera(void);
	void drawCube();
	void resetCamera(void);
	void Reshape(GLint, GLint);
	void Display(void);
};

