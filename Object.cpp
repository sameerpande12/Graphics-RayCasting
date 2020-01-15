#include "Object.h"
#include <cmath>
Object::Object(int Id,glm::dvec3 ref,glm::dvec3 col,double refrac,glm::dvec3 specColor,double specCoeff,double diffCoeff,double specExp,double k_trans,double k_reflec){
    id = Id;
    reference = ref;
    color = col;
    refractiveIndex = refrac;
    specularCoefficient = specCoeff;
    shininess = specExp;
    specularColor = specColor;
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

glm::dvec3 Object::getLocalIllumination(std::vector<PointSource> sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint){
    glm::dvec3 cLocal = glm::dvec3(0,0,0);
    glm::dvec3 cAmbient = glm::dvec3(0,0,0);
    glm::dvec3 cDifEffective = glm::dvec3(0,0,0);
    glm::dvec3 cSpecEfffective = glm::dvec3(0,0,0);

    glm::dvec3 v = glm::normalize(eye - contactPoint);
    


    for(int i = 0;i<(int)sources.size();i++){
        cAmbient = cAmbient +  sources[i].ambientCoefficient * color * sources[i].color;//sources[i].color represents the intensity of light source

        
        glm::dvec3 l = glm::normalize(sources[i].position-contactPoint);
        glm::dvec3 h = glm::normalize(v + l);//assume normal is normalized


        double ldotn = glm::dot(l,normal);
        if(ldotn<0)ldotn=0;

        cDifEffective = cDifEffective + ldotn * color * sources[i].color;
        
        double ndoth = glm::dot(normal,h);
        if(ndoth<0)ndoth = 0;
        double ndoth_exp = pow(ndoth,shininess);

        cSpecEfffective = cSpecEfffective + ndoth_exp * specularColor * sources[i].color;
    }

    cLocal = cSpecEfffective + cDifEffective + cAmbient;
    
    // for(int i = 0;i<sources.size();i++){
    //     glm::dvec3 l = glm::normalize(sources[i].position-contactPoint);
    //     glm::dvec3 h = glm::normalize(v + l);//assume normal is normalized


        // glm::dvec3 cLight = sources[i].color;//cLight definition could be modified to include the effect of distance from source

        // double ldotn = glm::dot(l,normal);
        // if(ldotn<0)ldotn=0;
        // cDifEffective = cDifEffective + (diffusionCoefficient * cLight) * ldotn;

        // double ndoth = glm::dot(normal,h);
        // if(ndoth<0)ndoth = 0;
        // glm::dvec3 specContribCoefficient = glm::dvec3(pow(ndoth,specularExponent[0]),pow(ndoth,specularExponent[1]),pow(ndoth,specularExponent[2]));
        // cSpecEfffective = cSpecEfffective + (specularCoefficient * cLight)* specContribCoefficient;
    // }

    // cLocal = cSpecEfffective + cDifEffective + ambientCoefficient * cAmbient;

    // for(int i =0 ;i<3;i++){
    //     if(cLocal[i]>1)cLocal[i]=1;
    // }

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

glm::dvec3 Object::getColor(){
    return color;
}

void Object::setColor(glm::dvec3 colour){
    color = colour;
}

double Object::getRefractiveIndex(){
    return refractiveIndex;
}

void Object::setRefractiveIndex(double refrac){
    refractiveIndex = refrac;
}
