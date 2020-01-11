#pragma once

#include <vector>
#include <math.h>

struct Color{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
};
std::vector<double> solveQuadratic(double a, double b, double c);