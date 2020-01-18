#include "Cylinder.h"
#include <glm/glm.hpp>
#include<limits>
#include <tuple>
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
Cylinder::Cylinder(int id,glm::dvec3 refer,glm::dvec3 col,double h,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec, int type):Object(id,refer,color,refrac,specColor,specCoeff,diffCoeff, specExp,k_trans,k_reflec,type){
    setHeight(h);
};

double absolute(double x){
    if(x>0)return x;
    return -x;
}

bool Cylinder::isInside(glm::dvec3 point){
    glm::dvec3 reference = getReference();
    bool tmp1 = (point[1] <= reference[1]+height/2) && ( reference[1]-height/2 <= point[1]);
    bool tmp2 = ((point[0] - reference[0])*(point[0] - reference[0]) + (point[2] - reference[2])*(point[2] - reference[2]) <= radius*radius)  ;
    return tmp1&&tmp2;
};

std::tuple<double,glm::dvec3,glm::dvec3> Cylinder::getClosestIntersection(Ray ray){
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
    
    bool isLateralIntersection = true;

    for(int i = 0;i<(int)roots.size();i++){
        if(roots[i]>=0){
            glm::dvec3 point = org + roots[i] * dir;
            
            if( absolute(point[1] - reference[1]) <= height/2 ){
                // intersections.push_back(ray.scale(roots[i]));
                if(roots[i] <= tmin)tmin =roots[i];
            }
            
        }
    }

    if(isinf(tmin))isLateralIntersection = false;

    // if(intersections.size()==2){
    //     return intersections;
    // }
    //Computer intersections with base
    // else{
        //y = reference[1]+ height/2
        
    if(dir[1] == 0.0){//do not consider intersections with base
        glm::dvec3 intersection = ray.scale(tmin); 
        glm::dvec3 normal = intersection - reference;
        reference[1]=0;
        normal = glm::normalize(normal);
        if(isInside(ray.getOrigin()))normal = -normal;
        return std::make_tuple(tmin,intersection, normal);
    }

    glm::dvec3 normal;
    for(int i =0 ;i<1;i++){
        double h = height;
        if(i%2==0)h = -h;
        double t = reference[1] + h/2 - org[1];
        t/=dir[1];
        
        if(t>=0){
            if(glm::length( ray.scale(t) - (reference+h/2)) <= radius){
                if(t<=tmin ){
                    tmin = t;
                    isLateralIntersection = false;
                    if(h>0)
                        normal = glm::dvec3(0,1,0);
                    else normal = glm::dvec3(0,-1,0);
                }
                // intersections.push_back(ray.scale(t));
            }    
        }
    }

    // }
    // return intersections;


    
    if(isLateralIntersection){
        glm::dvec3 intersection = ray.scale(tmin);
        normal = intersection - reference;
        normal[1] = 0;
        normal = glm::normalize(normal);
        if(isInside(ray.getOrigin()))normal = -normal;
        return std::make_tuple(tmin,intersection,normal);
    }
    if(isInside(ray.getOrigin()))normal = -normal;
    return std::make_tuple(tmin,ray.scale(tmin),normal);


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