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
        glm::dvec3 reference;
        struct Color color;
    public:

        Object(int id,glm::dvec3 reference,struct Color color);
        void setId(int id);
        void setReference(glm::dvec3 ref);
        void setColor(struct Color col);
        int getID();
        glm::dvec3 getReference();
        struct Color getColor();

};