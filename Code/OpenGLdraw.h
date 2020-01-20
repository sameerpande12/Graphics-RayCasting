
#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
class OpenGLdraw {
public:
   void init(int W, int H);
   void draw(GLubyte *image, GLuint W=0, GLuint H=0, int atx=0, int aty=0);
private:
	int width, height;
	GLuint fbo;
};