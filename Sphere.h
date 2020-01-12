#pragma once
#include "Object.h"
#include "Ray.h"
#include<iostream>
#include<vector>
#include<utility>

class Sphere : public Object{
    private:
        int radius;

    public:
        Sphere(int id,glm::dvec3 ref,struct Color color,int radius);
        std::pair<double,glm::dvec3> getIntersections(Ray ray);
        int getRadius();
        void setRadius(int rad);
};