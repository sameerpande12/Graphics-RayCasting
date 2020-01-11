#pragma once
#include<glm/glm.hpp>
#include "Ray.h"
#include <vector>

class Plane{
    public:
        glm::dvec3 normal;
        double d;
        //equation of the plane will be glm::dot(r,normal) = d;
        Plane(glm::dvec3 normal,double d);

        std::vector<glm::dvec3> getIntersections(Ray r);
};