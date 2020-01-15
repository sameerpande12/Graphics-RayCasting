
#include <vector>
#include <math.h>
#include"helper.h"
#include "Axes.h"
#include<limits>
#include <tuple>
#define INF std::numeric_limits<double>::infinity();
class Object;
std::vector<double> solveQuadratic(double a, double b, double c){
    std::vector<double>solutions;

    double discriminant = b*b - 4*a*c;
    if(discriminant <0)return solutions;

    if(discriminant == 0.0){
        solutions.push_back(-b/2/a);
    }
    else{
        solutions.push_back( (-b + sqrt(discriminant)  )/(2*a) );
        solutions.push_back( (-b - sqrt(discriminant)  )/(2*a) );
    }
    return solutions;

}


Axes rotateAxes(Axes input,double angle, int axisID){
    Axes output = Axes();
    output.x = rotateVector(input.x,angle,0);
    output.y = rotateVector(input.y,angle,1);
    output.z = rotateVector(input.z,angle,2);
    return output;
    
};

glm::dvec3 rotateVector(glm::dvec3 input,double angle, int axisID){

    glm::dmat3 rotation;
 
    if(axisID%3==0){

        rotation = glm::dmat3(  1,          0,          0,
                                0, cos(angle),-sin(angle),
                                0, sin(angle),cos(angle) );
    }
    else if(axisID%3==1){

        rotation = glm::dmat3(  cos(angle),          0,          sin(angle),
                                0,          1,          0,
                                -sin(angle),0, cos(angle) );

    }

    else{
        rotation = glm::dmat3(
            cos(angle), -sin(angle),0,
            sin(angle),cos(angle),0,
            0,0,1
        );

    }

    return rotation * input;

}
std::vector<bool> isShadow(glm::dvec3 point, std::vector<PointSource> sources,std::vector<Object*>objects){

    std::vector<bool> shadowVec;

    for(int i =0;i<(int)sources.size();i++){

        double tSource = glm::length(point - sources[i].position);
        Ray shadowRay = Ray(point, glm::normalize(sources[i].position-point),1);

        double tMIN = INF;
        for(int i = 0;i<(int)(objects.size());i++){
                std::tuple <double,glm::dvec3,glm::dvec3> intersection = objects[i]->getClosestIntersection(shadowRay);
                if(std::get<0>(intersection) >= 0 && std::get<0>(intersection) < tMIN){
                tMIN = std::get<0>(intersection);            
           }
        }

        if(tMIN >= 0 && tMIN < tSource)shadowVec.push_back(true);
        else shadowVec.push_back(false);
    }
    return shadowVec;
}

glm::dvec3 rayTrace(Ray ray, std::vector<Object*> objects, std::vector<PointSource>lightSources,int depth, int maxDepth,glm::dvec3 backgroundColor){
    if(depth > maxDepth)return glm::dvec3(0,0,0);

    int closestIntersectionIndex=-1;
    double closest_Tval = INF;
    double inf = INF;
    glm::dvec3 closestIntersectionPoint = glm::dvec3(inf,inf,inf);
    std::tuple <double,glm::dvec3,glm::dvec3> intersection;
    glm::dvec3 normal;

    
    for(int i =0 ;i<(int)(objects.size());i++){
         intersection = objects[i]->getClosestIntersection(ray);

        if(    std::get<0>(intersection) >= 0 && std::get<0>(intersection) < closest_Tval){
            closest_Tval = std::get<0>(intersection);
            closestIntersectionPoint = std::get<1>(intersection);
            normal = std::get<2>(intersection);
            closestIntersectionIndex = i;
        }
    };

    if(closestIntersectionIndex==-1){
        return backgroundColor;
    }

    std::vector<bool> shadowVec = isShadow(closestIntersectionPoint,lightSources,objects);


    std::vector<PointSource> accessibleSources;
    for(int i =0;i<(int)lightSources.size();i++){
        if( !shadowVec[i])accessibleSources.push_back(lightSources[i]);
    }
    
    glm::dvec3 localIllumination = glm::dvec3(0,0,0);
    // for(int i =0;i<(int)(objects.size());i++){
    localIllumination = localIllumination + objects[closestIntersectionIndex]->getLocalIllumination(accessibleSources,normal,ray.getOrigin(),closestIntersectionPoint);
    

    double Kr = objects[closestIntersectionIndex]->getK_Reflection();
    Ray reflectedRay = getReflectedRay(normal,ray,closestIntersectionPoint);
    glm::dvec3 reflectionContribution =  rayTrace(reflectedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);

    double Kt = objects[closestIntersectionIndex]->getK_Transmission();
    Ray refractedRay = getRefractedRay(normal,ray,closestIntersectionPoint,ray.getMediumRefractiveIndex(),objects[closestIntersectionIndex]->getRefractiveIndex());
    glm::dvec3 refractionRayContribution =  rayTrace(refractedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);

    return localIllumination + refractionRayContribution * Kt + reflectionContribution * Kr;


};

glm::dvec3 getReflectionDirection(glm::dvec3 normal,glm::dvec3 incident){
    //assumes normal is normalized
    return incident - 2*( glm::dot(normal,incident))*normal;
};



Ray getReflectedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point,double refractiveIndex){
    glm::dvec3 dir = getReflectionDirection(normal,incident);

    return  Ray(point,dir,refractiveIndex);
}

Ray getReflectedRay(glm::dvec3 normal,Ray incident, glm::dvec3 point){
    return getReflectedRaySubRoutine(normal,incident.getDirection(),point,incident.getMediumRefractiveIndex());
}

glm::dvec3 getRefractionDirection(glm::dvec3 normal,glm::dvec3 incident, double incomingRefractiveIndex,double outgoingRefractiveIndex){
    glm::dvec3 t;//stands for transmitted
    glm::dvec3 m;//stands for intermediate ray in plane formed by surface. Also in plane formed by normal and incident ray

    double cosAlpha = - glm::dot(normal,incident)/(glm::length(normal) * glm::length(incident));

    double n_relative = outgoingRefractiveIndex/incomingRefractiveIndex;

    double temp = 1 + n_relative*n_relative * ( cosAlpha*cosAlpha -1);
    if(temp<0){
        return getReflectionDirection(normal,incident);
    }
    t = -n_relative*incident + normal*( n_relative*cosAlpha - sqrt(temp) );

    return t;

};


Ray getRefractedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex){

    glm::dvec3 dir = getRefractionDirection(normal,incident,incomingRefractiveIndex,outgoingRefractiveIndex);
    return Ray(point,dir,outgoingRefractiveIndex);
};

Ray getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex){
    return getRefractedRaySubRoutine(normal,incident.getDirection(),point,incomingRefractiveIndex,outgoingRefractiveIndex);
}