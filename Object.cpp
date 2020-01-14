#include "Object.h"
#include <cmath>
Object::Object(int Id,glm::dvec3 ref,struct Color col,double refrac,glm::dvec3 ambCoefficient,glm::dvec3 specCoeff,glm::dvec3 diffCoeff,glm::dvec3 specExp,double k_trans,double k_reflec){
    id = Id;
    reference = ref;
    color = col;
    refractiveIndex = refrac;
    ambientCoefficient = ambCoefficient;
    specularExponent = specExp;
    specularCoefficient = specCoeff;
    diffusionCoefficient = diffusionCoefficient;
    k_transmission = k_trans;
    k_reflection = k_reflec;
};

double Object::getK_Transmission(){
        return k_transmission;
};
double Object::getK_Reflection(){
        return k_reflection;
};

glm::dvec3 Object::getLocalIllumination(std::vector<PointSource> sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint,glm::dvec3 ambientColor){
    glm::dvec3 cLocal = glm::dvec3(0,0,0);
    // glm::dvec3 cAmb = glm::dvec3(ambientColor.red,ambientColor.blue,ambientColor.green);
    glm::dvec3 cAmb = ambientColor;
    glm::dvec3 cDifEffective = glm::dvec3(0,0,0);
    glm::dvec3 cSpecEfffective = glm::dvec3(0,0,0);

    glm::dvec3 v = glm::normalize(eye - contactPoint);
    
    
    for(int i = 0;i<sources.size();i++){
        glm::dvec3 l = glm::normalize(sources[i].position-contactPoint);
        glm::dvec3 h = glm::normalize(v + l);//assume normal is normalized
        glm::dvec3 cLight = sources[i].color;//cLight definition could be modified to include the effect of distance from source

        double ldotn = glm::dot(l,normal);
        if(ldotn<0)ldotn=0;
        cDifEffective = cDifEffective + (diffusionCoefficient * cLight) * ldotn;

        double ndoth = glm::dot(normal,h);
        if(ndoth<0)ndoth = 0;
        glm::dvec3 specContribCoefficient = glm::dvec3(pow(ndoth,specularExponent[0]),pow(ndoth,specularExponent[1]),pow(ndoth,specularExponent[2]));
        cSpecEfffective = cSpecEfffective + (specularCoefficient * cLight)* specContribCoefficient;
    }

    cLocal = cSpecEfffective + cDifEffective + ambientCoefficient * cAmb;

    for(int i =0 ;i<3;i++){
        if(cLocal[i]>1)cLocal[i]=1;
    }

    return cLocal;

}

void Object::setId(int Id){
    id = Id;
}

int Object::getID(){
    return id;
}

void Object::setReference(glm::dvec3 ref){
    reference = ref;
}

glm::dvec3 Object::getReference(){
    return reference;
}

struct Color Object::getColor(){
    return color;
}

void Object::setColor(struct Color colour){
    color = colour;
}

double Object::getRefractiveIndex(){
    return refractiveIndex;
}

void Object::setRefractiveIndex(double refrac){
    refractiveIndex = refrac;
}
