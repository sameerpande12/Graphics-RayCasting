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
        
        Box(int id, glm::dvec3 ref, struct Color color, glm::dvec3 min, glm::dvec3 max, double side,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff, glm::dvec3 specExp);
        double getSide();
        void setSide(double len);

        std::pair <double,glm::dvec3> getFirstIntersection(Ray r);//if the double value is < 0 then assume that does not exist



};