#include "Box.h"
#include <tuple>
#include<limits>
#define INF std::numeric_limits<double>::infinity();

double Box::getSide(){
    return side;
}
void Box::setSide(double len){
    side = len;
}

bool Box::isInside(glm::dvec3 point){
    for(int i =0 ;i<3;i++){

        if( point[i]> maxBound[i])return false;
        if(point[i]<minBound[i])return false;
    }
    return true;
}

Box::Box(int id, glm::dvec3 ref, glm::dvec3 color, glm::dvec3 minimum, glm::dvec3 maximum,double len,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec):Object(id,ref,color,refrac,specColor,specCoeff,diffCoeff, specExp,k_trans,k_reflec){
    side = len;
    minBound = minimum;
    maxBound = maximum; 
}

std::tuple<double,glm::dvec3,glm::dvec3> Box::getClosestIntersection(Ray ray){
    glm::dvec3 org = ray.getOrigin();
    glm::dvec3 dir = ray.getDirection();
    
    
    double tmin = INF;
    glm::dvec3 normal = glm::dvec3(tmin,tmin,tmin);
    double t;

    int indexVal;
    bool fromMinBound;
    for(int i = 0;i<3;i++){
        if(dir[i]!=0.0){

            t = (minBound[i]-org[i])/dir[i];
            if(t>=0 && t <= tmin ){
                tmin = t;
                fromMinBound = true;
                indexVal = i;
            }
            

            t =  (maxBound[i]-org[i])/dir[i];
            if(t>=0 && t <= tmin ){
                fromMinBound = false;
                tmin = t;
                indexVal = i;
            }
        }
    }
    glm::dvec3 normal;
    if(indexVal==0)normal = glm::dvec3(1,0,0);
    if(indexVal==1)normal = glm::dvec3(0,1,0);
    else normal = glm::dvec3(0,0,1);

    if(!fromMinBound)normal = -normal;
    return std::make_tuple(tmin,ray.scale(tmin),normal);
    
    
}