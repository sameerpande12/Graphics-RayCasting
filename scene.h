#pragma once
#include "PointSource.h"
#include <vector>
#include "Object.h"
#include "Sphere.h"
#include "Wall.h"
#include "Camera.h"
void createScene(std::vector<PointSource*>&lightSources,std::vector<Sphere*>&shinyBalls,std::vector<Sphere*>&snowSpheres,std::vector<Wall*>&walls,std::vector<Object*>&objects,double R,int width,int height);