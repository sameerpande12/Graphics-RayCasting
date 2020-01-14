#pragma once
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include<iostream>
#include "helper.h"
#include "PointSource.h"

class Object{


    protected:
        int id;
        glm::dvec3 reference;
        struct Color color;
        double refractiveIndex;
        glm::dvec3 ambientCoefficient;
        glm::dvec3 specularExponent;
        glm::dvec3 diffusionCoefficient;
        glm::dvec3 specularCoefficient;

    public:
        
        Object(int id,glm::dvec3 reference,struct Color color,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp);
        void setId(int id);
        void setReference(glm::dvec3 ref);
        void setColor(struct Color col);
        int getID();
        glm::dvec3 getReference();
        struct Color getColor();

        void setRefractiveIndex(double refractiveIndex);
        double getRefractiveIndex();

        glm::dvec3 getLocalIllumination(std::vector<PointSource> sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint,struct Color ambientColor);

};