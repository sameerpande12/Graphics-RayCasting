#include "Cube.h"

double Cube::getSide(){
    return side;
};

void Cube::setSide(double sid){
    side = sid;
};

Cube::Cube(int id,glm::dvec3 ref,struct Color color,double side_V,Axes axes_n):Object(id,ref,color)
{
    side = side_V;
    axes = axes_n;
    computePlanes();    
}

Axes Cube::getAxes(){
    return axes;
}

void Cube::setAxes(Axes axes_){
    axes = axes_;
};

void Cube::computePlanes(){
    //assuming axes are of unit length and orthogonal to each other
    std::vector<Plane> new_planes;
    for(int i =0 ;i<3;i++){
        glm::dvec3 axis = axes.getAxis( (i+2)% 3);
        double d = glm::dot(axis,getReference());
        new_planes.push_back( Plane(axis,d-side/2));
        new_planes.push_back( Plane(axis,d+side/2));
    }
    planes = new_planes;

};
std::vector<Plane> Cube::getPlanes(){
    return planes;
};
void Cube::setPlanes(std::vector<Plane> new_planes){
    planes = new_planes;   
};
