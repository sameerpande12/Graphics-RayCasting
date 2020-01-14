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
        double k_transmission;
        double k_reflection;

    public:
        
        Object(int id,glm::dvec3 reference,struct Color color,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp,double k_trans,double k_reflec);
        void setId(int id);
        void setReference(glm::dvec3 ref);
        void setColor(struct Color col);
        int getID();
        glm::dvec3 getReference();
        struct Color getColor();

        void setRefractiveIndex(double refractiveIndex);
        double getRefractiveIndex();

        double getK_Transmission();
        double getK_Reflection();

        glm::dvec3 getLocalIllumination(std::vector<PointSource> sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint,glm::dvec3 ambientColor);

        virtual std::tuple<double,glm::dvec3,glm::dvec3> getClosestIntersection(Ray ray)=0;//returns t_val, intersection_point, normal_vector at that point
        virtual bool isInside(glm::dvec3 point);//make sure not to use for points which are doubtful to be on the surface
};