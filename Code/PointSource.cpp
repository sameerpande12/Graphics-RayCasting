#include "PointSource.h"

PointSource::PointSource(glm::dvec3 pos,glm::dvec3 col,double att,double ambientCoeff){
    color = col;
    position = pos;
    ambientCoefficient = ambientCoeff;
    attenuation = att;
}