#include "Plane.h"
#include<glm/glm.hpp>
Plane::Plane(glm::dvec3 norm,double dval){
    normal = normal;
    d = dval;
}

std::vector<glm::dvec3> Plane::getIntersections(Ray ray){
    std::vector<glm::dvec3> intersections;
    double normal_dir_dot_product =glm::dot(normal,ray.getDirection());
    if(  normal_dir_dot_product== 0.0){
        if( glm::dot(normal,ray.getOrigin())==d){
            intersections.push_back(ray.getOrigin());
        }   
        
    }
    else{
        double t = (d - glm::dot(normal,ray.getOrigin())) /normal_dir_dot_product;
        intersections.push_back(ray.scale(t));
    }
    return intersections;

};