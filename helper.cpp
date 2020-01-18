
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
std::vector<bool> isShadow(glm::dvec3 point, std::vector<PointSource*> &sources,std::vector<Object*>&objects){

    std::vector<bool> shadowVec;

    for(int i =0;i<(int)sources.size();i++){

        double tSource = glm::length(point - sources[i]->position);
        Ray shadowRay = Ray(point, glm::normalize(sources[i]->position-point),1);

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

glm::dvec3 rayTrace(Ray ray, std::vector<Object*> &objects, std::vector<PointSource*>&lightSources,int depth, int maxDepth,glm::dvec3 backgroundColor){
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


    std::vector<PointSource*> accessibleSources;
    for(int i =0;i<(int)lightSources.size();i++){
        if( !shadowVec[i])accessibleSources.push_back(lightSources[i]);
    }
    
    glm::dvec3 localIllumination = glm::dvec3(0,0,0);
    
    localIllumination = localIllumination + objects[closestIntersectionIndex]->getLocalIllumination(accessibleSources,normal,ray.getOrigin(),closestIntersectionPoint);
    // localIllumination = localIllumination + objects[closestIntersectionIndex]->getLocalIllumination(lightSources,normal,ray.getOrigin(),closestIntersectionPoint);

    double Kr = objects[closestIntersectionIndex]->getK_Reflection();
    glm::dvec3 reflectionContribution = glm::dvec3(0,0,0);
    if(Kr!=0){
        // if(objects[closestIntersectionIndex]->getType()==0){
        //     std::cout<<Kr<<" <- Kr"<<std::endl;
        // }
        Ray reflectedRay = getReflectedRay(normal,ray,closestIntersectionPoint);
        reflectionContribution =  rayTrace(reflectedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);
    }

    double Kt = objects[closestIntersectionIndex]->getK_Transmission();
    glm::dvec3 refractionRayContribution = glm::dvec3(0,0,0);
    
    // std::cout<<"Object number: "<<objects[closestIntersectionIndex]->getID()<<" Kt:"<<Kt<<std::endl;
    
    // bool tmp = objects[closestIntersectionIndex]->isInside(closestIntersectionPoint);
    // std::cout<<"Intersection Point -> ("<<closestIntersectionPoint[0]<<","<<closestIntersectionPoint[1]<<","<<closestIntersectionPoint[2]<<") isInside "<<tmp<<"\n";
    if(Kt!=0){
        // if(objects[closestIntersectionIndex]->getType()==0){
        //     std::cout<<Kt<<" <- Kt"<<std::endl;
        // }
        closest_Tval = closest_Tval + 2* 0.001;
        closestIntersectionPoint = ray.scale(closest_Tval);
        // tmp = objects[closestIntersectionIndex]->isInside(closestIntersectionPoint);
        // std::cout<<"Refracted Intersection Point -> ("<<closestIntersectionPoint[0]<<","<<closestIntersectionPoint[1]<<","<<closestIntersectionPoint[2]<<") isInside "<<tmp<<"\n";
        bool isInsideObject = (ray.getMediumRefractiveIndex()==objects[closestIntersectionIndex]->getRefractiveIndex()); 
        // std::cout<<"Incoming ray direction: "<<ray.getDirection()[0]<<" "<<ray.getDirection()[1]<<" "<<ray.getDirection()[2]<<"\n";
        
        if(objects[closestIntersectionIndex]->getType()==0){
            normal = glm::normalize(closestIntersectionPoint - objects[closestIntersectionIndex]->getReference());
            if(isInsideObject)normal = -normal;
        }
        // std::cout<<"normal direction: "<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<"\n";
        if(!isInsideObject){
            Ray refractedRay = getRefractedRay(normal,ray,closestIntersectionPoint,ray.getMediumRefractiveIndex(),objects[closestIntersectionIndex]->getRefractiveIndex());
            // std::cout<<"Outgooing refraction ray direction: "<<refractedRay.getDirection()[0]<<" "<<refractedRay.getDirection()[1]<<" "<<refractedRay.getDirection()[2]<<"\n\n";
            refractionRayContribution =  rayTrace(refractedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);
        }
        else{ 
            Ray refractedRay = getRefractedRay(normal,ray,closestIntersectionPoint,ray.getMediumRefractiveIndex(),1);
            // std::cout<<"Outgooing refraction ray direction: "<<refractedRay.getDirection()[0]<<" "<<refractedRay.getDirection()[1]<<" "<<refractedRay.getDirection()[2]<<"\n\n";
            refractionRayContribution =  rayTrace(refractedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);
            
        }
        // std::cout<<refractionRayContribution[0]<<" "<<refractionRayContribution[1]<<" "<<refractionRayContribution[2]<<"\n";
    }
    
    return localIllumination + refractionRayContribution * Kt + reflectionContribution * Kr;


};

// glm::dvec3 getReflectionDirection(glm::dvec3 normal,glm::dvec3 incident){
//     //assumes normal is normalized
//     return incident - 2*( glm::dot(normal,incident))*normal;
// };



// Ray getReflectedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point,double refractiveIndex){
//     glm::dvec3 dir = getReflectionDirection(normal,incident);

//     return  Ray(point,dir,refractiveIndex);
// }

Ray getReflectedRay(glm::dvec3 normal,Ray incident, glm::dvec3 point){
    glm::dvec3 direction = incident.getDirection() - 2* glm::dot(incident.getDirection(),normal)*normal;
    return Ray(point,direction,incident.getMediumRefractiveIndex());
    // return getReflectedRaySubRoutine(normal,incident.getDirection(),point,incident.getMediumRefractiveIndex());
}


Ray getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex){
    //assume that the incoming point has already been adjusted for by increasing t_val by 0.0001
    glm::dvec3 t;
    glm::dvec3 v = incident.getDirection();
    double n = incomingRefractiveIndex/outgoingRefractiveIndex;

    double cosAlpha =  glm::dot( -normal,v);//assuming all the directions are unit vectors
    double discriminant = 1 + (cosAlpha*cosAlpha -1)/(n*n);
    if(discriminant<0){
        //you will have to reduce the t_value
        point = point - 0.0002 *(incident.getDirection());//make sure you take away the point out before reflection;
        return getReflectedRay(normal,incident,point);//this also keeps the ray in the same medium it came from
    }
    
    t = glm::normalize(v/n  + normal*(  cosAlpha/n - sqrt(discriminant)));
    return Ray(point,t,outgoingRefractiveIndex);
}