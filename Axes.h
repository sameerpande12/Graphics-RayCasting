#pragma once
#include <glm/glm.hpp>
class Axes{
    public:
        glm::dvec3 x;
        glm::dvec3 y;
        glm::dvec3 z;
        //should follow the property that the x y and z are of unit length
        // x X y = z, y X z = x, z X x = y
        glm::dvec3 getAxis(int id);
        void setAxes(glm::dvec3 a, glm::dvec3 b, glm::dvec3 c);
        Axes();
        Axes(glm::dvec3 X,glm::dvec3 Y,glm::dvec3 Z);
        
};