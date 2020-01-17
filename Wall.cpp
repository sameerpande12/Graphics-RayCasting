#include "Wall.h"
#include <glm/glm.hpp>
#include<tuple>
#define INF std::numeric_limits<double>::infinity();
Wall::Wall(int id,glm::dvec3 minBou, glm::dvec3 maxBou,glm::dvec3 ref,glm::dvec3 color,glm::dvec4 params,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec):Object(id,ref,color,refrac,specColor,specCoeff,diffCoeff, specExp,k_trans,k_reflec){
    setParameters(params);
    if(params[0]==0 && params[1]==0){
        normalDir = 2;
    }
    else if(params[1]==0 && params[2]==0){
        normalDir = 0;
    }
    else if(params[2]==0 && params[0]==0){
        normalDir = 1;
    }
    else normalDir = -1;
    minBounds = minBou;
    maxBounds = maxBou;
    
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

    glm::dvec3 intersection = ray.scale(tmp);
    bool bounded = true;
    for(int i =0;i<3;i++){

        if(i==normalDir)continue;
        if (!( (intersection[i] <= maxBounds[i]) && (intersection[i]>=minBounds[i]))){
            bounded = false;
            break;
        }

    }
    glm::dvec3 normal = initParams3;
    if(bounded){
        if(tmp >= 0)tmin = tmp;
        if(tmin > 0.0001)tmin -= 0.0001;
        if(glm::dot(normal,ray.getDirection()) > 0)normal = -normal;

    }
    
    return std::make_tuple(tmin, ray.scale(tmin), normal);

};
