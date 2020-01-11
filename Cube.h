#pragma once
#include "Object.h"
#include "Plane.h"
#include<vector>
#include "Axes.h"

class Cube:public Object{
    private:
        double side;
        std::vector<Plane> planes;
        Axes axes;
        

    public:
        double getSide();
        void setSide(double side);
        
        Cube(double side,glm::dvec3 reference, Axes axes);
        

        std::vector<Plane> getPlanes();
        void setPlane(Plane p,int i);

        Axes getAxes();
        void setAxes(Axes axes_);

        void computePlanes();//given side and axes compute the set of planes
         
    
    
}