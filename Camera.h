#pragma once
#include<math.h>
#include "Axes.h"
#include<glm/glm.hpp>
#include "helper.h"
class Camera{
    private:
        double aspectRatio;

    public:
        

        glm::dvec3 location;
        Axes axes;
        int width;
        int height;
        double fov = M_PI_2;// pi/2
        Camera(glm::dvec3 location,Axes axes,int width,int height,double fov);

        glm::dvec3 cameraToWorld(glm::dvec3 input);
        glm::dvec3 pixelToCamera(double i, double j);//i,j are pixel numbers. ought to be integers but we have kept it as double for the ease of computation

        glm::dvec3 pixelToWorld(double i,double j); 

        void moveCamera(glm::dvec3 displacement);
        
        void rotateCamera(double angle, int axisID);

        // screen follow coordinate system
    /*                 
                        y
                        ^
                        |
                        |
                        |(0,0)
                        ------------> x
                        width is along x
                        height is along y
        */  
        


};