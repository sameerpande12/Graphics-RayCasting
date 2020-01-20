#include "Wall.h"
#include <glm/glm.hpp>
#include<tuple>
#define INF std::numeric_limits<double>::infinity();


Wall::Wall(int id,std::vector<glm::dvec3>cornerPoints,glm::dvec3 ref,glm::dvec3 color,double refrac,double scale,double diffCoeff,double roughness,double k_trans,double k_reflec,double d,int type,bool visible):Object(id,ref,color,refrac,scale,diffCoeff,roughness,k_trans,k_reflec,d,type,visible){
    updatePoints(cornerPoints);
}

void Wall::updatePoints(std::vector<glm::dvec3>cornerPoints){
    
    glm::dvec3 alongNormal = glm::normalize(glm::cross( cornerPoints[0]-cornerPoints[1],cornerPoints[0]-cornerPoints[2]));
    double d = glm::dot(alongNormal,cornerPoints[0]);
    setParameters(glm::dvec4(alongNormal,d));
    points = cornerPoints;
    xnew = glm::normalize(cornerPoints[1]-cornerPoints[0]);
    ynew = glm::normalize(cornerPoints[3]-cornerPoints[0]);
    xLength = glm::length(cornerPoints[1]-cornerPoints[0]);
    yLength = glm::length(cornerPoints[3]-cornerPoints[0]); 

}

std::vector<glm::dvec3> Wall::getPoints(){return points;}
void Wall::setParameters(glm::dvec4 params){
    parameters = params;
}
bool Wall::isInside(glm::dvec3 point){
    if( glm::dot(point,glm::dvec3(parameters)) != parameters[3])return false;

    glm::dvec3 displacementFromCornerZero = point - points[0];

    double xVal = glm::dot(xnew,displacementFromCornerZero);
    double yVal = glm::dot(ynew,displacementFromCornerZero);
     return (xVal <= xLength) && (xVal>=0) && (yVal<=yLength) && (yVal >= 0);

}

bool Wall::isInsideGivenOnPlane(glm::dvec3 point){
    
    glm::dvec3 displacementFromCornerZero = point - points[0];

    double xVal = glm::dot(xnew,displacementFromCornerZero);
    double yVal = glm::dot(ynew,displacementFromCornerZero);
     return (xVal <= xLength) && (xVal>=0) && (yVal<=yLength) && (yVal >= 0);    
}

glm::dvec4 Wall::getParameters(){
    return parameters;
}

std::tuple<double,glm::dvec3,glm::dvec3> Wall::getClosestIntersection(Ray ray){
    double tmin = INF;
    glm::dvec3 dir = (ray.getDirection());//assuming ray direction is already normalized
    glm::dvec3 initParams3 = glm::dvec3(parameters);
    double tmp = parameters[3] - glm::dot(ray.getOrigin(), initParams3);
    
    double denom = glm::dot(dir,initParams3);
    if(denom==0){
        return std::make_tuple(tmin,ray.scale(tmin),initParams3);
    }
    tmp = tmp / denom;

    glm::dvec3 intersection = ray.scale(tmp);
    bool bounded = isInsideGivenOnPlane(intersection);
    // for(int i =0;i<3;i++){

    //     if(i==normalDir)continue;
    //     if (!( (intersection[i] <= maxBounds[i]) && (intersection[i]>=minBounds[i]))){
    //         bounded = false;
    //         break;
    //     }

    // }
    glm::dvec3 normal = initParams3;
    if(bounded){
        if(tmp >= 0)tmin = tmp;
        if(tmin > 0.0001)tmin -= 0.0001;
        if(glm::dot(normal,ray.getDirection()) > 0)normal = -normal;

    }
    
    return std::make_tuple(tmin, ray.scale(tmin), normal);

};
