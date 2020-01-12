#pragma once
#include "Object.h"
#include "Ray.h"
class Cylinder: public Object{
    private:
        
        double height;
        double radius;
    public:
        
        void setHeight(double height);
        double getHeight();

        void setRadius(double radius);
        double getRadius();

        Cylinder(int id,glm::dvec3 reference,struct Color color,double height);
        


        std::vector<glm::dvec3> getIntersections(Ray r);
};