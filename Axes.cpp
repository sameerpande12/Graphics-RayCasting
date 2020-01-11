#include "Axes.h"
#include <glm/glm.hpp>

glm::dvec3 Axes::getAxis(int id){
    if(id%3==0)return x;
    else if(id%3==1)return y;
    else return z;
}
