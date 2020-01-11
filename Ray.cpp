#include "Ray.h"


glm::vec3 Ray::getDirection(){
    return direction;
}

glm::vec3 Ray::getOrigin(){
    return origin;
}

void Ray::setDirection(glm::vec3 dir){
    direction = dir;
}

void Ray::setOrigin(glm::vec3 org){
    origin = org;
}