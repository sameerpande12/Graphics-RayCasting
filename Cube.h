#pragma once
#include "Object.h"
#include "Plane.h"
#include<vector>
#include "Axes.h"

class Cube : public Object{
    private:
        double side;
        std::vector<Plane> planes;
        Axes axes;
        

    public:
        Cube(double side ,glm::dvec3 ref);
        double getSide();
        void setSide(double side);
        
        std::vector<Plane> getPlanes();
        void setPlanes(std::vector<Plane> new_planes);

        
        

        std::vector<Plane> getPlanes();
        void setPlane(Plane p,int i);

        Axes getAxes();
        void setAxes(Axes axes_);

        void computePlanes();//given side and axes compute the set of planes
         
        

        
    
};