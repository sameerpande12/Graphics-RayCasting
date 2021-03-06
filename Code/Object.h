#pragma once
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include<iostream>
#include "helper.h"
#include "PointSource.h"
#include "Ray.h"

class Object{


    protected:
        int id;
        glm::dvec3 reference;
        glm::dvec3 color;
        double refractiveIndex;
        double scalingFactor;
        double roughness;
        double diffusionCoefficient;
        // glm::dvec3 specularColor;
        double k_transmission;
        double k_reflection;
        int type;//0 for sphere, 1 for wall,2 for cylinder
        bool visible;
        double dVal;
        double sVal;

        double fresnelConstant;//not fresnalFactor

    public:
        bool isVisible();
        void setVisibility(bool visibility);
        Object(int id,glm::dvec3 reference,glm::dvec3 color,double refrac,double scale,double diffCoeff,double roughVal,double k_trans,double k_reflec,double d,int typ,bool isVisible);
        void setId(int id);
        void setReference(glm::dvec3 ref);
        void setColor(glm::dvec3 col);
        int getID();
        glm::dvec3 getReference();
        glm::dvec3 getColor();

        void setRefractiveIndex(double refractiveIndex);
        double getRefractiveIndex();

        int getType();

        double getK_Transmission();
        double getK_Reflection();

        double getS();
        double getD();
        double getFresnelConstant();
        double getRoughness();


        double getScalingFactor();
        double getDiffusionCoefficient();

        virtual glm::dvec3 getLocalIllumination(std::vector<PointSource*> &sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint);

        virtual std::tuple<double,glm::dvec3,glm::dvec3> getClosestIntersection(Ray ray)=0;//returns t_val, intersection_point, normal_vector at that point
        virtual bool isInside(glm::dvec3 point)=0;//make sure not to use for points which are doubtful to be on the surface
};