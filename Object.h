#pragma once
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include<iostream>


struct Color{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
};
class Object{


    private:
        int id;
        glm::vec3 reference;
        struct Color color;
    public:

        Object(int id,glm::vec3 reference,struct Color color);
        void setId(int id);
        void setReference(glm::vec3 ref);
        void setColor(struct Color col);
        int getID();
        glm::vec3 getReference();
        struct Color getColor();

};