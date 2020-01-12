#include "Sphere.h"
#include "helper.h"
#include<limits>
#define INF std::numeric_limits<double>::infinity();
int Sphere::getRadius(){
    return radius;
}
void Sphere::setRadius(int rad){
    radius =rad;
}

Sphere::Sphere(int id,glm::dvec3 ref,struct Color color,int radius):Object(id,ref,color){
    setRadius(radius);
}

std::pair<double,glm::dvec3>Sphere::getIntersections(Ray ray){
    // std::vector<glm::dvec3> intersections;
    double tmin = INF;
    double a,b,c;
    a = 1.0;
    b = 2* glm::dot(ray.getDirection(),  ray.getOrigin()- reference);
    c = (glm::length(ray.getOrigin()- reference));
    c = c*c - getRadius()*getRadius();

    std::vector<double> roots = solveQuadratic(a,b,c);

    for(int i =0 ;i<roots.size();i++){
        if(roots[i]>=0 && roots[i]<=tmin ){
            tmin = roots[i];
            // intersections.push_back(ray.getOrigin()+ roots[i]*ray.getDirection());
        }
    }
    return std::make_pair(tmin,ray.scale(tmin));    
}

