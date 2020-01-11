#include "Cube.h"

double Cube::getSide(){
    return side;
}

void Cube::setSide(double sid){
    side = sid;
}

Cube::Cube(double side_ ,glm::dvec3 ref,Axes axes_){
    side = side_;
    setReference(ref);
    axes = axes_;
}


Axes Cube::getAxes(){
    return axes;
}

void Cube::setAxes(Axes axes_){
    axes = axes_;

    
}

