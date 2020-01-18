#pragma once
#include "Object.h"
class Wall:public Object{//working only for walls aligned along x , y , z
    protected:
        glm::dvec4 parameters;//ax + by +cz = d (a,b,c,d) is the equation 
        glm::dvec3 minBounds;//
        glm::dvec3 maxBounds;
        int normalDir;//0 for x , 1 for y, 2 for z;//
    public:
        Wall(int id,glm::dvec3 minbound, glm::dvec3 maxbound,glm::dvec3 ref,glm::dvec3 color,glm::dvec4 equation,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec,int type);
        std::tuple<double,glm::dvec3,glm::dvec3>getClosestIntersection(Ray ray);
        glm::dvec4 getParameters();
        void setParameters(glm::dvec4 params);
        bool isInside(glm::dvec3 point);
};