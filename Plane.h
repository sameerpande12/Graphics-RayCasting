#pragma once
#include<glm/glm.hpp>

class Plane{
    public:
        glm::dvec3 normal;
        double d;
        //equation of the plane will be glm::dot(r,normal) = d;
        Plane(glm::dvec3 normal,double d);
};