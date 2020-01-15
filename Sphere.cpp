#include "Sphere.h"
#include "helper.h"
#include<limits>
#include <tuple>
#define INF std::numeric_limits<double>::infinity();
int Sphere::getRadius(){
    return radius;
}
void Sphere::setRadius(int rad){
    radius =rad;
}

Sphere::Sphere(int id,glm::dvec3 ref,glm::dvec3 color,int radius,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec):Object(id,ref,color,refrac,specColor,specCoeff,diffCoeff, specExp,k_trans,k_reflec){
    setRadius(radius);
}


bool Sphere::isInside(glm::dvec3 point){
    return (glm::length(point - getReference())< radius);
};
std::tuple<double,glm::dvec3,glm::dvec3>Sphere::getClosestIntersection(Ray ray){
    // std::vector<glm::dvec3> intersections;
    double tmin = INF;
    double a,b,c;
    a = 1.0;
    b = 2* glm::dot(ray.getDirection(),  ray.getOrigin()- reference);
    c = (glm::length(ray.getOrigin()- reference));
    c = c*c - getRadius()*getRadius();

    std::vector<double> roots = solveQuadratic(a,b,c);

    for(int i =0 ;i<(int)roots.size();i++){
        if(roots[i]>=0 && roots[i]<=tmin ){
            tmin = roots[i];
            // intersections.push_back(ray.getOrigin()+ roots[i]*ray.getDirection());
        }
    }

    glm::dvec3 intersection = ray.scale(tmin);
    glm::dvec3 normal = glm::normalize(intersection - getReference());
    if(isInside(ray.getOrigin()))normal = -normal;
    return std::make_tuple(tmin,intersection,normal);    
}

glm::dvec3 Sphere::getNormal(glm::dvec3 intersection){
    return glm::normalize(intersection -  getReference());
};
