#pragma once4

#include <glm/glm.hpp>
class PointSource{
    public:
        glm::dvec3 position;
        glm::dvec3 color;//vector of (R,G,B); each between 0 to 1
        PointSource(glm::dvec3 position, glm::dvec3 color);
        
};