#pragma once

#include <vector>
#include <math.h>
#include "GL/glew.h"
#include "Axes.h"
#include "Object.h"
#include "Ray.h"
#include "PointSource.h"

struct Color{
    double red;
    double green;
    double blue;//all the values wiill be kept within 0 and 1
};
class Object;
std::vector<double> solveQuadratic(double a, double b, double c);

Axes rotateAxes(Axes input,double angle, int axisID);//rotate axes by an angle about axisID (0 for x, 1 for y , 2 for z)
glm::dvec3 rotateVector(glm::dvec3 input,double angle, int axisID);//rotate by an angle about axis with axisID(0 for x, 1 for y, 2 for z)

glm::dvec3 rayTrace(Ray ray, std::vector<Object*> objects, std::vector<PointSource>lightSources,int depth, int maxDepth,glm::dvec3 backgroundColor);

glm::dvec3 getReflectionDirection(glm::dvec3 normal,glm::dvec3 incident);
Ray getReflectedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point,double getRefractiveIndex);
Ray getReflectedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point);


glm::dvec3 getRefractionDirection(glm::dvec3 normal,glm::dvec3 incident, double incomingRefractiveIndex,double outgoingRefractiveIndex);
Ray getRefractedRaySubRoutine(glm::dvec3 normal,glm::dvec3 incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex);
Ray getRefractedRay(glm::dvec3 normal,Ray incident,glm::dvec3 point, double incomingRefractiveIndex,double outgoingRefractiveIndex);

std::vector<bool> isShadow(glm::dvec3 point, std::vector<PointSource> sources,std::vector<Object*>objects);