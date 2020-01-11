#include "Object.h"

Object::Object(int Id,glm::dvec3 ref,struct Color col){
    id = Id;
    reference = ref;
    color = col;
};

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
