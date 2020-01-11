#pragma once
#include <glm/glm.hpp>

class Ray{

    private:
        glm::vec3 origin;
        glm::vec3 direction;

    public:
        int id;

        glm::vec3 getOrigin();
        glm::vec3 getDirection();
        void setDirection(glm::vec3 dir);
        void setOrigin(glm::vec3 org);
};