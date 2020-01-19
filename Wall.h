#pragma once
#include "Object.h"
class Wall:public Object{
    protected:
        glm::dvec4 parameters;//ax + by +cz = d (a,b,c,d) is the equation 
        std::vector<glm::dvec3> points;
        glm::dvec3 xnew;
        glm::dvec3 ynew;
        double xLength;
        double yLength;
    public:
        
        Wall(int id,std::vector<glm::dvec3>cornerPoints,glm::dvec3 ref,glm::dvec3 color,double refrac,double scale,double diffCoeff,double roughness,double k_trans,double k_reflec,double d,int type,bool visible=false);
        //cornerPoints are given in antiClockWise/clockWise Direction
        //Walls are assumed to be rectangular
        std::tuple<double,glm::dvec3,glm::dvec3>getClosestIntersection(Ray ray);
        glm::dvec4 getParameters();
        void setParameters(glm::dvec4 params);
        bool isInside(glm::dvec3 point);
        void updatePoints(std::vector<glm::dvec3>cornerPoints);
        bool isInsideGivenOnPlane(glm::dvec3 point);
        std::vector<glm::dvec3>getPoints();
};