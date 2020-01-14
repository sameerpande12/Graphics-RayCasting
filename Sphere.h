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
        Sphere(int id,glm::dvec3 ref,struct Color color,int radius,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp,double k_trans,double k_reflec);
        std::tuple<double,glm::dvec3,glm::dvec3> getClosestIntersection(Ray ray);
        int getRadius();
        void setRadius(int rad);
        glm::dvec3 getNormal(glm::dvec3 intersection);
        bool isInside(glm::dvec3 point);
};