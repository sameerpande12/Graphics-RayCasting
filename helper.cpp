
#include <vector>
#include <math.h>
#include"helper.h"
#include "Axes.h"
#include<limits>
#include <tuple>
#define INF std::numeric_limits<double>::infinity();
class Object;
void printAxes(Axes ax){
    
    for(int i = 0;i<3;i++){
        glm::dvec3 axis = ax.getAxis(i);
        std::cout<<"(";
        for(int j=0;j<3;j++){
            std::cout<<axis[j];
            if(j<2)std::cout<<",";
        }
        std::cout<<") ";
    }
    std::cout<<std::endl;
}

void printVector(glm::dvec3 vec){
    std::cout<<"("<<vec[0]<<","<<vec[1]<<","<<vec[2]<<")\n";
}
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
    output.x = rotateVector(input.x,angle,axisID);
    output.y = rotateVector(input.y,angle,axisID);
    output.z = rotateVector(input.z,angle,axisID);
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
            if(objects[i]->getType()==2)continue;//ignore the cylinders while consider shadow
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
        if(depth==1 && !objects[i]->isVisible()){continue;}
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
    if(objects[closestIntersectionIndex]->getType()==2){//
        return localIllumination;
    }

    double Kr = objects[closestIntersectionIndex]->getK_Reflection();
    glm::dvec3 reflectionContribution = glm::dvec3(0,0,0);
    if(Kr!=0){
        
        Ray reflectedRay = getReflectedRay(normal,ray,closestIntersectionPoint);
        reflectionContribution =  rayTrace(reflectedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);
    }

    double Kt = objects[closestIntersectionIndex]->getK_Transmission();
    glm::dvec3 refractionRayContribution = glm::dvec3(0,0,0);
    
    
    if(Kt!=0){
        
        closest_Tval = closest_Tval + 2* 0.0001;
        closestIntersectionPoint = ray.scale(closest_Tval);
    
        bool isInsideObject = (ray.getMediumRefractiveIndex()==objects[closestIntersectionIndex]->getRefractiveIndex()); 
    
        if(!isInsideObject){
            Ray refractedRay = getRefractedRay(normal,ray,closestIntersectionPoint,ray.getMediumRefractiveIndex(),objects[closestIntersectionIndex]->getRefractiveIndex());
           
            refractionRayContribution =  rayTrace(refractedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);
        }
        else{ 
            Ray refractedRay = getRefractedRay(normal,ray,closestIntersectionPoint,ray.getMediumRefractiveIndex(),1);
           
            refractionRayContribution =  rayTrace(refractedRay,objects,lightSources,depth+1,maxDepth,backgroundColor);
            
        }
        
    }
    // printVector(refractionRayContribution);
    
    return localIllumination + refractionRayContribution * Kt + reflectionContribution * Kr;


};


Ray getReflectedRay(glm::dvec3 normal,Ray incident, glm::dvec3 point){
    glm::dvec3 direction = incident.getDirection() - 2* glm::dot(incident.getDirection(),normal)*normal;
    return Ray(point,direction,incident.getMediumRefractiveIndex());

}


Ray getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex){
    //assume that the incoming point has already been adjusted for by increasing t_val by 0.0001
    glm::dvec3 t;
    glm::dvec3 v = incident.getDirection();
    double n = incomingRefractiveIndex/outgoingRefractiveIndex;

    double cosAlpha =  glm::dot( -normal,v);//assuming all the directions are unit vectors
    // std::cout<<"Cos Alpha "<<cosAlpha<<"\n";
    double discriminant = 1 + (cosAlpha*cosAlpha -1)/(n*n);
    if(discriminant<0){
        //you will have to reduce the t_value
        point = point - 0.0002 *(incident.getDirection());//make sure you take away the point out before reflection;
        // std::cout<<"TOTAL INTERNAL REFLECTION"<<"\n";
        return getReflectedRay(normal,incident,point);//this also keeps the ray in the same medium it came from
    }
    
    t = glm::normalize(v/n  + normal*(  cosAlpha/n - sqrt(discriminant)));
    return Ray(point,t,outgoingRefractiveIndex);
}