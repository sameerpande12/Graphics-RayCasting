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
};