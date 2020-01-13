
#include <vector>
#include <math.h>
#include"helper.h"
#include "Axes.h"

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


Axes rotate(Axes input,double angle, int axisID){
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