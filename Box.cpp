#include "Box.h"
#include<limits>
#define INF std::numeric_limits<double>::infinity();

double Box::getSide(){
    return side;
}
void Box::setSide(double len){
    side = len;
}

Box::Box(int id, glm::dvec3 ref, struct Color color, glm::dvec3 minimum, glm::dvec3 maximum,double len,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp):Object(id,ref,color,refrac,ambCoefficient,specCoeff,diffCoeff, specExp){
    side = len;
    minBound = minimum;
    maxBound = maximum; 
}

std::pair<double,glm::dvec3> Box::getFirstIntersection(Ray ray){
    glm::dvec3 org = ray.getOrigin();
    glm::dvec3 dir = ray.getDirection();
    
    
    double tmin = INF;
    double t;

    for(int i = 0;i<3;i++){
        if(dir[i]!=0.0){

            t = (minBound[i]-org[i])/dir[i];
            if(t>=0 && t <= tmin ){
                tmin = t;
            }
            

            t =  (maxBound[i]-org[i])/dir[i];
            if(t>=0 && t <= tmin ){
                tmin = t;
            }
        }
    }

    return std::make_pair(tmin,ray.scale(tmin));
    
    
}