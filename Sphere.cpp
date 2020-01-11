#include "Sphere.h"
#include "helper.h"
int Sphere::getRadius(){
    return radius;
}
void Sphere::setRadius(int rad){
    radius =rad;
}

Sphere::Sphere(int id,glm::dvec3 ref,struct Color color,int radius):Object(id,ref,color){
    setRadius(radius);
}

std::vector<glm::dvec3> Sphere::getIntersections(Ray ray){
    std::vector<glm::dvec3> intersections;
    
    double a,b,c;
    a = 1.0;
    b = 2* glm::dot(ray.getDirection(),  ray.getOrigin()- getReference());
    c = (glm::length(ray.getOrigin()- getReference()));
    c = c*c - getRadius()*getRadius();

    std::vector<double> roots = solveQuadratic(a,b,c);

    for(int i =0 ;i<roots.size();i++){
        intersections.push_back(ray.getOrigin()+ roots[i]*ray.getDirection());
    }
    return intersections;    
}

