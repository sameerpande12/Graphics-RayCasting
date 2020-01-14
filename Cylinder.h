#pragma once
#include "Object.h"
#include "Ray.h"
#include <utility>
class Cylinder: public Object{
    private:
        
        double height;
        double radius;
    public:
        
        void setHeight(double height);
        double getHeight();

        void setRadius(double radius);
        double getRadius();

        Cylinder(int id,glm::dvec3 reference,struct Color color,double height,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp);
        


        std::pair<double ,glm::dvec3> getIntersections(Ray r);
};