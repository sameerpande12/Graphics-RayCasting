#include "Wall.h"
#include <glm/glm.hpp>
#include<tuple>
#define INF std::numeric_limits<double>::infinity();
Wall::Wall(int id,glm::dvec3 ref,glm::dvec3 color,glm::dvec4 params,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec):Object(id,ref,color,refrac,specColor,specCoeff,diffCoeff, specExp,k_trans,k_reflec){
    setParameters(params);
}
void Wall::setParameters(glm::dvec4 params){
    parameters = params;
}
bool Wall::isInside(glm::dvec3 point){
    double diff = glm::dot(glm::dvec3(parameters),point)-parameters[3];
    return (diff==0);
}

glm::dvec4 Wall::getParameters(){
    return parameters;
}

std::tuple<double,glm::dvec3,glm::dvec3> Wall::getClosestIntersection(Ray ray){
    double tmin = INF;
    glm::dvec3 dir = glm::normalize(ray.getDirection());
    glm::dvec3 initParams3 = glm::dvec3(parameters);
    double tmp = parameters[3] - glm::dot(ray.getOrigin(), initParams3);
    tmp = tmp / ( glm::dot(dir,initParams3)  );

    if(tmp >= 0)tmin = tmp;

    if(tmin > 0.0001)tmin -= 0.0001;

    glm::dvec3 normal = initParams3;
    if(glm::dot(normal,ray.getDirection()) > 0)normal = -normal;

    return std::make_tuple(tmin, ray.scale(tmin), normal);

};
