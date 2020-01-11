#include "Ray.h"

Ray::Ray(glm::dvec3 org,glm::dvec3 dir){
    origin = org;
    direction =dir;
}

glm::dvec3 Ray::getDirection(){
    return direction;
}

glm::dvec3 Ray::getOrigin(){
    return origin;
}

void Ray::setDirection(glm::dvec3 dir){
    direction = glm::normalize(dir);
}

void Ray::setOrigin(glm::dvec3 org){
    origin = org;
}

glm::dvec3 Ray::scale(double t){
    return origin + t*direction;
}
