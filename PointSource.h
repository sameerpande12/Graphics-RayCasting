#pragma once4

#include <glm/glm.hpp>
class PointSource{
    public:
        glm::dvec3 position;
        glm::dvec3 color;//vector of (R,G,B); each between 0 to 1
        double attenuation;
        double ambientCoefficient;
        PointSource(glm::dvec3 position, glm::dvec3 color,double attenuation,double ambientCoeff);
        
};