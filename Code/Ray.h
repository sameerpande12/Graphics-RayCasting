#pragma once
#include <glm/glm.hpp>

class Ray{

    protected:
        glm::dvec3 origin;
        glm::dvec3 direction;
        double mediumRefractiveIndex=1;    
        
    
    public:
        int id;
        Ray(glm::dvec3 origin,glm::dvec3 direction,double refrac);
        glm::dvec3 getOrigin();
        glm::dvec3 getDirection();
        void setDirection(glm::dvec3 dir);
        void setOrigin(glm::dvec3 org);
        glm::dvec3 scale(double t);
        
        double getMediumRefractiveIndex();

        // glm::dvec3 getReflectionDirection(glm::dvec3 normal,glm::dvec3 incident);
        // Ray getReflectedRay(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point,double getRefractiveIndex);
        // Ray getReflectedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point);


        // glm::dvec3 Ray::getRefractionDirection(glm::dvec3 normal,glm::dvec3 incident, double incomingRefractiveIndex,double outgoingRefractiveIndex);
        // Ray getRefractedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex);
        // Ray getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex);
};
