#pragma once
#include "Object.h"
#include "Ray.h"
#include<iostream>
#include<vector>

class Sphere : public Object{
    private:
        int radius;

    public:
        std::vector<glm::dvec3> getIntersections(Ray ray);
        int getRadius();
        void setRadius(int rad);
};