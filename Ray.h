#pragma once
#include <glm/glm.hpp>

class Ray{

    private:
        glm::dvec3 origin;
        glm::dvec3 direction;

    public:
        int id;
        Ray(glm::dvec3 origin,glm::dvec3 direction);
        glm::dvec3 getOrigin();
        glm::dvec3 getDirection();
        void setDirection(glm::dvec3 dir);
        void setOrigin(glm::dvec3 org);
        glm::dvec3 scale(double t);

        glm::dvec3 getReflectionDirection(glm::dvec3 normal,glm::dvec3 incident);
        Ray getReflectedRay(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point);
        Ray getReflectedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point);

        glm::dvec3 Ray::getRefractionDirection(glm::dvec3 normal,glm::dvec3 incident, double incomingRefractiveIndex,double outgoingRefractiveIndex);
        Ray getRefractedRay(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex);
        Ray getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex)
};