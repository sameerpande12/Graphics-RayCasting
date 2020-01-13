#pragma once

#include <vector>
#include <math.h>
#include "GL/glew.h"


struct Color{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
};
std::vector<double> solveQuadratic(double a, double b, double c);

Axes rotateAxes(Axes input,double angle, int axisID);//rotate axes by an angle about axisID (0 for x, 1 for y , 2 for z)
glm::dvec3 rotateVector(glm::dvec3 input,double angle, int axisID);//rotate by an angle about axis with axisID(0 for x, 1 for y, 2 for z)