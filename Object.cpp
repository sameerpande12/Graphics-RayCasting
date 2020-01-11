#include "Object.h"

void Object::setId(int Id){
    id = Id;
}

int Object::getID(){
    return id;
}

void Object::setReference(glm::vec3 ref){
    reference = ref;
}

glm::vec3 Object::getReference(){
    return reference;
}

struct Color Object::getColor(){
    return color;
}

void Object::setColor(struct Color colour){
    color = colour;
}