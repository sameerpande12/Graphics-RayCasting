#pragma once
#include "Object.h"
#include "Ray.h"
#include "PointSource.h"
#include <utility>
class Cylinder: public Object{
    private:
        
        double height;
        double radius;
        Axes axes;
        std::vector<PointSource*> pointSources;
    public:
        
        void setHeight(double height);
        double getHeight();

        void setRadius(double radius);
        double getRadius();

        void setAxes(Axes ax);
        Axes getAxes();//the y axis is along the length

        Cylinder(int id,glm::dvec3 lightColour, double lightAttenuation,double lightAmbientCoeff,Axes axis,glm::dvec3 reference,double radius,glm::dvec3 color,double height,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec,int type,bool visible);
        std::vector<PointSource*> getPointSources();


        std::tuple<double ,glm::dvec3,glm::dvec3> getClosestIntersection(Ray r);
        glm::dvec3 getNormal(glm::dvec3 intersection);
         bool isInside(glm::dvec3 point);

         glm::dvec3 getLocalIllumination(std::vector<PointSource*> &sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint);
         void updatePosition(glm::dvec3 newRef, Axes newAxes);
};