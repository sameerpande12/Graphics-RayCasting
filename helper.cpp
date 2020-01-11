
#include <vector>
#include <math.h>
#include"helper.h"

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
