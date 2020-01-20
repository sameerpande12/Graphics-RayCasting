#include "Object.h"
#include <cmath>
Object::Object(int Id,glm::dvec3 ref,glm::dvec3 col,double refrac,double scale,double diffCoeff,double roughVal,double k_trans,double k_reflec,double d,int typ,bool isVi){
    id = Id;
    type = typ;
    reference = ref;
    color = col;
    refractiveIndex = refrac;
    scalingFactor = scale;
    roughness = roughVal;
    diffusionCoefficient = diffCoeff;
    k_transmission = k_trans;
    k_reflection = k_reflec;
    visible=isVi;
    dVal = d;
    sVal = 1-d;
    double tmp = ( refractiveIndex - 1)/(refractiveIndex + 1);
    fresnelConstant = tmp*tmp;

};
int Object::getType(){
    return type;
}
bool Object::isVisible(){
    return visible;
}
double Object::getK_Transmission(){
        return k_transmission;
};
double Object::getK_Reflection(){
        return k_reflection;
};
void Object::setVisibility(bool visi){
    visible = visi;
}
double Object::getS(){return sVal;}
double Object::getD(){return dVal;}
double Object::getFresnelConstant(){return fresnelConstant;}

double Object::getScalingFactor(){return scalingFactor;};
double Object::getDiffusionCoefficient(){return diffusionCoefficient;};
double Object::getRoughness(){return roughness;};

double getG(double a, double b, double c){//assume a is positive always
    if(b<0)b=0;
    if(c<0)c = 0;

    double minVal = a;
    if(minVal>b)minVal = b;
    if(minVal>c)minVal = c;
    return minVal;
}

glm::dvec3 Object::getLocalIllumination(std::vector<PointSource*> &sources,glm::dvec3 normal,glm::dvec3 eye,glm::dvec3 contactPoint){
    
    glm::dvec3 cLocal = glm::dvec3(0,0,0);
    glm::dvec3 cAmbient = glm::dvec3(0,0,0);
    glm::dvec3 cDifEffective = glm::dvec3(0,0,0);
    glm::dvec3 cSpecEfffective = glm::dvec3(0,0,0);

    glm::dvec3 v = glm::normalize(eye - contactPoint);
    


    for(int i = 0;i<(int)sources.size();i++){
        cAmbient = cAmbient +  sources[i]->ambientCoefficient * color * (sources[i]->color);//sources[i]->color represents the intensity of light source

        if(dVal==0){
            
        }
        glm::dvec3 l = glm::normalize(sources[i]->position-contactPoint);
        glm::dvec3 h = glm::normalize(v + l);//assume normal is normalized
        double ldotn = glm::dot(l,normal);
        if(ldotn<0)ldotn=0;

        double distance = glm::length(contactPoint - sources[i]->position);
        glm::dvec3 effColor = color *sources[i]->color/(1 + distance*distance*sources[i]->attenuation);
        cDifEffective = cDifEffective + ldotn *effColor;

        if(sVal==0){
           continue;
        } 
        
        double ndotv = glm::dot(normal,v);
        double hdotv = glm::dot(v,h);
        double hdotn = glm::dot(normal,h);

        double F = fresnelConstant + (1-fresnelConstant)*pow(1- hdotv,5);
        double G = getG(1, 2*hdotn*ndotv/hdotv,2*hdotn*ldotn/hdotv); 

        double mSquare = roughness*roughness;

        double secSquareAlpha = 1/(hdotn*hdotn);

        double D = secSquareAlpha*secSquareAlpha * exp(  (1-secSquareAlpha)/mSquare  ) /(  mSquare *M_PI  );
        
        double rs = D*G*F/(4/**ldotn*/*ndotv);//delibarately removing ndotl since we won't multiply it here then
        if(rs<0)rs=0;    
        
        cSpecEfffective = cSpecEfffective + rs*effColor;

    }
    
    // cLocal = scalingFactor* cSpecEfffective + dVal* diffusionCoefficient* cDifEffective + cAmbient;
    cLocal = sVal* cSpecEfffective *scalingFactor + (dVal* diffusionCoefficient* cDifEffective) + cAmbient;
                                        // d * kd * (n.l) *
    // cLocal = (dVal* diffusionCoefficient* cDifEffective);
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
