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

        Cylinder(int id,glm::dvec3 reference,struct Color color,double height,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp,double k_trans,double k_reflec);
        


        std::tuple<double ,glm::dvec3,glm::dvec3> getClosestIntersection(Ray r);
        glm::dvec3 getNormal(glm::dvec3 intersection);
         bool isInside(glm::dvec3 point);
};