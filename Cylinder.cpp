#include "Cylinder.h"
#include "Plane.h"
#include <glm/glm.hpp>
#include<limits>
#define INF std::numeric_limits<double>::infinity();

void Cylinder::setHeight(double h){
    height = h;
};
double Cylinder::getHeight(){
    return height;
};

void Cylinder::setRadius(double rad){
    radius = rad;
}

double Cylinder::getRadius(){
    return radius;
}
Cylinder::Cylinder(int id,glm::dvec3 refer,struct Color col,double h,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp):Object(id,refer,color,refrac,ambCoefficient,specCoeff,diffCoeff, specExp){
    setHeight(h);
};

double absolute(double x){
    if(x>0)return x;
    else -x;
}
std::pair<double,glm::dvec3> Cylinder::getIntersections(Ray ray){
    //the axis is (0,1,0)

    /*intersections with the walls/lateral surface*/
    
    // (Ox + tdx)^2 + (Oz + tdz)^2 = radius^2


    // std::vector<glm::dvec3> intersections;
    double tmin = INF;

    double a,b,c;
    glm::dvec3 dir = ray.getDirection();
    glm::dvec3 org = ray.getOrigin();
    a = (dir[0] + dir[2])*(dir[0] + dir[2]);
    b = 2*( dir[0]*org[0]+ dir[2]*org[2]);
    c = (org[0]*org[0] + org[2]*org[2] - radius*radius);

    std::vector<double> roots = solveQuadratic(a,b,c);
    
    for(int i = 0;i<roots.size();i++){
        if(roots[i]>=0){
            glm::dvec3 point = org + roots[i] * dir;
            
            if( absolute(point[1] - reference[1]) <= height/2 ){
                // intersections.push_back(ray.scale(roots[i]));
                if(roots[i] <= tmin)tmin =roots[i];
            }
            
        }
    }
    // if(intersections.size()==2){
    //     return intersections;
    // }
    //Computer intersections with base
    // else{
        //y = reference[1]+ height/2
        
    if(dir[1] == 0.0){//do not consider intersections with base 
        return std::make_pair(tmin,ray.scale(tmin));
    }

    double heights[2];
    for(int i =0 ;i<1;i++){
        double h = height;
        if(i%2==0)h = -h;
        double t = reference[1] + h/2 - org[1];
        t/=dir[1];
        
        if(t>=0){
            if(glm::length( ray.scale(t) - (reference+h/2)) <= radius){
                if(t<=tmin )tmin = t;
                
                // intersections.push_back(ray.scale(t));
            }    
        }
    }

    // }
    // return intersections;
    return std::make_pair(tmin,ray.scale(tmin));


}

// std::vector<glm::dvec3> Cylinder::getIntersections(Ray ray){
//     std::vector<glm::dvec3> intersections;
//     std::vector<glm::dvec3> intersections1;

//     double cons1 = glm::dot(axis,getReference() + height/2 * axis );
//     Plane base1 = Plane(axis,cons1);    
//     intersections1 = base1.getIntersections(ray);
//     bool intersect1 = false;
//     if(intersections1.size()>0){
//         if(  glm::length(  getReference() + height/2 * axis - intersections1[0]) <= radius){
//             intersections.push_back(intersections1[0]);
//         }
//     }


//     double cons2 = glm::dot(axis,getReference() - height/2 * axis );
//     Plane base2 = Plane(axis,cons2);
//     std::vector<glm::dvec3> intersections2 = base2.getIntersections(ray);
//     if(intersections2.size()>0){
//         if(glm::length(getReference()-height/2*axis - intersections2[0]) <= radius){
//             intersections.push_back(intersections2[0]);
//         }
//     }
//     if(intersections.size()<2){
        
//     }

// }