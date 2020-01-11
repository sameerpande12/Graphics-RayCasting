#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define QUIT(m,v)      { fprintf(stderr, "%s:%s\n", m, v); exit(1); }

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

class OpenGLdraw {
public:
   void init(int W, int H) {
      
      unsigned int texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
  
      width = W; height = H;
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, W, H, 0,
             GL_RGB, GL_UNSIGNED_BYTE, NULL);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
      glGenFramebuffers(1, &fbo);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
      glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
   }

   void draw(GLubyte *image, GLuint W=0, GLuint H=0, int atx=0, int aty=0) {
      if(H == 0) H = height;
      if(W == 0) W = width;
      glTexSubImage2D(GL_TEXTURE_2D, 0, atx, aty, W, H, GL_RGB, GL_UNSIGNED_BYTE, image);

      glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
      glBlitFramebuffer(0, 0, W, H, atx, aty, W, H,
                     GL_COLOR_BUFFER_BIT, GL_NEAREST);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
      GLenum err = glGetError();
      std::cout<<err<<std::endl;

   }
private:
	int width, height;
	GLuint fbo;
};

int main( int argc, char* args[] )
{
   int M, m;

    if (!glfwInit())
        QUIT("gWindow_GLFW", "Could not Initialize GLFW");
   

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwSetErrorCallback(error_callback);

    bool coreProfile = true;
    if(coreProfile) {
       glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__ 
       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
   }

    GLFWwindow *window = glfwCreateWindow(640, 480, "Simple", NULL, NULL);
    if (!window) {
        glfwTerminate();
        QUIT("gWindow_GLFW", "Could not create Window");
    }

    glfwMakeContextCurrent(window);

    if ( GLEW_OK != glewInit() ) {
        glfwTerminate();
        QUIT("gWindow_GLFW","glewInit failed");
    }
   
   glGetError();
    glfwSwapInterval(1);

   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   printf("Width = %d, Height = %d\n", width, height);
   // width -= 5;

   glEnable(GL_TEXTURE_2D);
   OpenGLdraw opengl;
   opengl.init(width, height);
   GLubyte data[1280*1024*3];
   GLubyte color = 10;
   while (!glfwWindowShouldClose(window))
   {
      for(int i=0; i<3*width*height; i++) data[i] = color;
      // color += 10;
      glClearColor(0.5, 1, 1, 0.0);
      glClear(GL_COLOR_BUFFER_BIT);
      opengl.draw(data, 640, 480, 100, 100);
      glfwSwapBuffers(window);
      glfwPollEvents();
   }
            
   glfwTerminate();
   return 0;
}
