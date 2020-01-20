#include "Ray.h"

Ray::Ray(glm::dvec3 org,glm::dvec3 dir,double refrac){
    origin = org;
    direction =dir;
    mediumRefractiveIndex = refrac;
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

double Ray::getMediumRefractiveIndex(){
    return mediumRefractiveIndex;
}

// glm::dvec3 Ray::getReflectionDirection(glm::dvec3 normal,glm::dvec3 incident){
//     //assumes normal is normalized
//     return incident - 2*( glm::dot(normal,incident))*normal;
// };

// Ray Ray::getReflectedRay(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point,double refractiveIndex){
//     glm::dvec3 dir = getReflectionDirection(normal,incident);

//     return  Ray(point,dir,refractiveIndex);
// }

// Ray Ray::getReflectedRay(glm::dvec3 normal,Ray incident, glm::dvec3 point){
//     getReflectedRay(normal,incident.getDirection(),point,incident.getRefractiveIndex());
// }

// glm::dvec3 Ray::getRefractionDirection(glm::dvec3 normal,glm::dvec3 incident, double incomingRefractiveIndex,double outgoingRefractiveIndex){
//     glm::dvec3 t;//stands for transmitted
//     glm::dvec3 m;//stands for intermediate ray in plane formed by surface. Also in plane formed by normal and incident ray

//     double cosAlpha = - glm::dot(normal,incident)/(glm::length(normal) * glm::length(incident));

//     double n_relative = outgoingRefractiveIndex/incomingRefractiveIndex;

//     double temp = 1 + n_relative*n_relative * ( cosAlpha*cosAlpha -1);
//     if(temp<0){
//         return getReflectionDirection(normal,incident);
//     }
//     t = -n_relative*incident + normal*( n_relative*cosAlpha - sqrt(temp) );

//     return t;

// };

// Ray Ray::getRefractedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex){

//     glm::dvec3 dir = getRefractionDirection(normal,incident,incomingRefractiveIndex,outgoingRefractiveIndex);
//     return Ray(point,dir,outgoingRefractiveIndex);
// };

// Ray Ray::getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex){
//     return getRefractedRaySubRoutine(normal,incident.getDirection(),point,incomingRefractiveIndex,outgoingRefractiveIndex);
// }
