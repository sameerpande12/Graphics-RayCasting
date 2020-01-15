#pragma once
#include "Object.h"
class Wall:public Object{
    protected:
        glm::dvec4 parameters;//ax + by +cz = d (a,b,c,d) is the equation 
    public:
        Wall(int id,glm::dvec3 ref,glm::dvec3 color,glm::dvec4 equation,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec);
        std::tuple<double,glm::dvec3,glm::dvec3>getClosestIntersection(Ray ray);
        glm::dvec4 getParameters();
        void setParameters(glm::dvec4 params);
        bool isInside(glm::dvec3 point);
};