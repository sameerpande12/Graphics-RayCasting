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

void Cylinder::setAxes(Axes ax){
    axes = ax;
}
Axes Cylinder::getAxes(){
    return axes;
}
Cylinder::Cylinder(int id,glm::dvec3 lightColour, double lightAttenuation,double lightAmbientCoeff,Axes ax,glm::dvec3 refer,double radius,glm::dvec3 col,double h,double refrac,double scale,double diffCoeff,double roughness,double k_trans,double k_reflec, double d,int type,bool visible):Object(id,refer,color,refrac,scale,diffCoeff, roughness,k_trans,k_reflec,d,type,visible){
    setHeight(h);
    setAxes(ax);
    setRadius(radius);
    std::vector<PointSource*> pointSrc;
    
    for(int i= 1;i<=4;i++){
        glm::dvec3 loc = refer - (  0.625 * height-  i*0.25*height)*ax.getAxis(1);
        
        pointSrc.push_back(new PointSource(loc,lightColour,lightAttenuation,lightAmbientCoeff   ));
    }
    pointSources = pointSrc;
};

void Cylinder::updatePosition(glm::dvec3 newRef, Axes newAxes){
    setReference(newRef);
    setAxes(newAxes);
    for(int i =1 ;i<=4;i++){//updating the position of new point sources
        glm::dvec3 loc = newRef - (height/2 - i*0.2*height)*newAxes.getAxis(1);
        pointSources[i-1]->position = loc;
    }

}

glm::dvec3 Cylinder::getLocalIllumination(std::vector<PointSource*> &sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint){
    glm::dvec3 localIllumination=glm::dvec3(0,0,0);
    for(int i =0;i<(int)pointSources.size();i++){
        localIllumination += pointSources[i]->color;
    }
    
    
    return localIllumination;

};

std::vector<PointSource*> Cylinder::getPointSources(){
    return pointSources;
}
double absolute(double x){
    if(x>0)return x;
    return -x;
}

bool Cylinder::isInside(glm::dvec3 point){
    glm::dvec3 relativePosition = point - getReference();
    bool heightCheck = (absolute( glm::dot(relativePosition,axes.getAxis(1))) <= height/2);
    bool radiusCheck = (glm::length(glm::cross(relativePosition,axes.getAxis(1))) <= radius);
    return radiusCheck && heightCheck;
};

std::tuple<double,glm::dvec3,glm::dvec3> Cylinder::getClosestIntersection(Ray ray){
    
    double tmin = INF;

    //check with lateral surface;
    //assume the direction of the ray is normalized
    glm::dvec3 dir = ray.getDirection();
    glm::dvec3 heightAxis = axes.getAxis(1);
    glm::dvec3 p = ray.getOrigin()-getReference();

    double dir_Axis_prod = glm::dot(dir,heightAxis);
    double p_Axis_prod = glm::dot(p,heightAxis);
    double p_dir_prod = glm::dot(p,dir);
    double a = -dir_Axis_prod*dir_Axis_prod + glm::dot(dir,dir);
    double b = -2*( p_Axis_prod)*(dir_Axis_prod) + 2*p_dir_prod;
    double c = -p_Axis_prod * p_Axis_prod + glm::dot(p,p) - radius*radius;

    std::vector<double> surfaceRoots = solveQuadratic(a,b,c);
    // bool onCurvedSurface = false;
    glm::dvec3 normal;
    for(int i = 0;i<(int)surfaceRoots.size();i++){
        if(surfaceRoots[i]>=0 && surfaceRoots[i]<=tmin){
            double tmp = surfaceRoots[i];
            
            glm::dvec3 tmpIntersection = ray.scale(tmp);
            glm::dvec3 relativePosition = tmpIntersection - getReference();
            if((absolute( glm::dot(relativePosition,heightAxis)) <= height/2)){
                tmin = surfaceRoots[i];
                // onCurvedSurface = true;
                normal = glm::normalize( relativePosition - glm::dot(relativePosition,heightAxis)*heightAxis );

            }
        }
    }

    if(dir_Axis_prod!=0.0){
        for(int i = 0;i<1;i++){

            double h = height;
            if(i%2==0) h = -h;

            double tempT = (h/2 - p_Axis_prod)/dir_Axis_prod;
            if(tempT < 0 || tempT >= tmin)continue;
            glm::dvec3 tmpIntersection = ray.scale(tempT);
            glm::dvec3 relativePosition = tmpIntersection - getReference();
            if(glm::length(glm::cross(relativePosition,heightAxis)) <= radius){
                tmin = tempT;
                // onCurvedSurface=false;
                normal = heightAxis;
                if(i%2==0)normal = -heightAxis;
            };

        }
    }

    if(isInside(ray.getOrigin()))normal = -normal;
    if(tmin > 0.0001)tmin-=0.0001;

    return std::make_tuple(tmin,ray.scale(tmin),normal);    
}