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
        Sphere(int id,glm::dvec3 ref,glm::dvec3 color,int radius,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec);
        std::tuple<double,glm::dvec3,glm::dvec3> getClosestIntersection(Ray ray);
        int getRadius();
        void setRadius(int rad);
        glm::dvec3 getNormal(glm::dvec3 intersection);
        bool isInside(glm::dvec3 point);
};