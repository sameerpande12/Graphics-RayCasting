#include "Plane.h"
#include<glm/glm.hpp>
#include<limits>
#define INF std::numeric_limits<double>::infinity();
Plane::Plane(glm::dvec3 norm,double dval){
    normal = normal;
    d = dval;
}

std::pair<double,glm::dvec3> Plane::getIntersections(Ray ray){
    // std::vector<glm::dvec3> intersections;
    double tmin = INF;
    double normal_dir_dot_product =glm::dot(normal,ray.getDirection());
    if(  normal_dir_dot_product== 0.0){
        if( glm::dot(normal,ray.getOrigin())==d){
            // intersections.push_back(ray.getOrigin())
            tmin =0;
        }   
        
    }
    else{
        double t = (d - glm::dot(normal,ray.getOrigin())) /normal_dir_dot_product;
        if(t>=0 && t <= tmin ){
            // intersections.push_back(ray.scale(t));
            tmin = t;
        }
    }
    return std::make_pair(tmin,ray.scale(tmin));

};