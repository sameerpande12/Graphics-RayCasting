#pragma once
#include "Object.h"
#include "Ray.h"
#include <utility>
class Cylinder: public Object{
    private:
        
        double height;
        double radius;
        Axes axes;
    public:
        
        void setHeight(double height);
        double getHeight();

        void setRadius(double radius);
        double getRadius();

        void setAxes(Axes ax);
        Axes getAxes();//the y axis is along the length

        Cylinder(int id,Axes axis,glm::dvec3 reference,double radius,glm::dvec3 color,double height,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec,int type,bool visible);
        


        std::tuple<double ,glm::dvec3,glm::dvec3> getClosestIntersection(Ray r);
        glm::dvec3 getNormal(glm::dvec3 intersection);
         bool isInside(glm::dvec3 point);
};