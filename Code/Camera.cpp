#include "Camera.h"

Camera::Camera(glm::dvec3 loc, Axes ax, int w, int h, double FOV){
    location = loc;
    axes = ax;
    width = w;
    height = h;
    fov = FOV;
    aspectRatio = width/height;
    
}

glm::dvec3 Camera::cameraToWorld(glm::dvec3 input){

    glm::dvec3 output = glm::dvec3(0,0,0);

    for(int i =0 ;i<3;i++){
        for(int j=0;j<3;j++){
            output[i]= output[i] + axes.getAxis(j)[i] * input[j];
        }
    }

    output = output + location;
    

    return output;
}

glm::dvec3 Camera::pixelToCamera(double px,double py){
    
    
    double pixelCamerax = (2* (px+0.5)/width - 1)  * aspectRatio * tan(fov/2);
    double pixelCameray = (2* (py + 0.5)/height - 1) * tan(fov/2);
    // pixelCameray = -pixelCameray;

    return glm::dvec3( pixelCamerax,pixelCameray,-1);



}

glm::dvec3 Camera::pixelToWorld(double px,double py){
    
    return  cameraToWorld(pixelToCamera(px,py));
}

void Camera::rotateCamera(double angle,int axisID){
    axes = rotateAxes(axes,angle,axisID);
}