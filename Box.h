#pragma once
#include "Object.h"
#include "Ray.h"
#include<utility>
class Box: public Object{
    protected:
        glm::dvec3 minBound;//minx, miny , minz
        glm::dvec3 maxBound;//max x , max y, max z
        double side;
        
    public:
        
        Box(int id, glm::dvec3 ref, glm::dvec3 color, glm::dvec3 min, glm::dvec3 max, double side,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec);
        double getSide();
        void setSide(double len);

        std::tuple <double,glm::dvec3,glm::dvec3> getClosestIntersection(Ray r);//if the double value is < 0 then assume that does not exist

        bool isInside(glm::dvec3 point);

};