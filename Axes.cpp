#include "Axes.h"
#include <glm/glm.hpp>

glm::dvec3 Axes::getAxis(int id){
    if(id%3==0)return x;
    else if(id%3==1)return y;
    else return z;
}

void Axes::setAxes(glm::dvec3 a, glm::dvec3 b, glm::dvec3 c){
    x = a;
    y = b;
    z = c;
};
Axes::Axes(){
    x = glm::dvec3(1,0,0);
    y = glm::dvec3(0,1,0);
    z = glm::dvec3(0,0,1);
}
Axes::Axes(glm::dvec3 X, glm::dvec3 Y, glm::dvec3 Z){
    x = glm::normalize(X);
    y = glm::normalize(Y);
    z = glm::normalize(Z);
}