#pragma once
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include<iostream>
#include "helper.h"


class Object{


    protected:
        int id;
        glm::dvec3 reference;
        struct Color color;
        double refractiveIndex;

    public:
        
        Object(int id,glm::dvec3 reference,struct Color color);
        void setId(int id);
        void setReference(glm::dvec3 ref);
        void setColor(struct Color col);
        int getID();
        glm::dvec3 getReference();
        struct Color getColor();

        void setRefractiveIndex(double refractiveIndex);
        double getRefractiveIndex();

};