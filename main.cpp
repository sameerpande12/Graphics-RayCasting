#include <iostream>
#include "Ray.h"
#include "PointSource.h"
#include "Sphere.h"
#include "Box.h"
#include "Camera.h"
#include "Object.h"
#include <glm/glm.hpp>
#include <fstream>
#define cout std::cout
#define endl std::endl

int image[640][640][3];
int main(){

    double R = 5;
    Axes xyz = Axes();
    int width = 640;
    int height = 640;
    int id = 1;

    xyz.setAxes(glm::dvec3(1,0,0),glm::dvec3(0,1,0),glm::dvec3(0,0,1));
    
    glm::dvec3 cameraPosition = glm::dvec3(2*R,2*R,0);
    // cameraPosition = glm::dvec3(0,2*R,0);
    Camera camera = Camera(cameraPosition,xyz,width,height,M_PI/2);


    glm::dvec3 lightSourceLocation = glm::dvec3(2*R,2*R,0);
    glm::dvec3 lightSourceIntensity = glm::dvec3(1,1,1);
    double attenuation = 0.01;
    double ambientCoefficient = 0.1;
    PointSource source = PointSource(lightSourceLocation,lightSourceIntensity,attenuation,ambientCoefficient);

    glm::dvec3 snowColor = glm::dvec3(.3,0,0.3);
    glm::dvec3 location = glm::dvec3(2*R,2*R,-2*R);
    glm::dvec3 snowSpecColor = glm::dvec3(1,1,1);
    double snowSpecCoeff = 0.5;
    double snowdiffCoeff = 0.6;

    double snowShininess = 0.3;
    
    double snowKtrans = 0;
    double snowKreflec = 0.1;
    double snowRadius = R/2;
    Sphere* sphere1 = new Sphere(id,location,snowColor,snowRadius,1.1,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec);
    
    id++;
    Sphere* sphere2 = new Sphere(id,glm::dvec3(3*R,2*R,-2*R),glm::dvec3(0,1,0),R/2,1.1,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec);

    std::vector<Object*> objects;
    std::vector<PointSource> lightSources;

    objects.push_back(sphere1);
    objects.push_back(sphere2);
    lightSources.push_back(source);
    
    std::ofstream myfile;
    myfile.open("image.csv");
    
    for(int i = 0;i<height;i++){
        for(int j=0;j<width;j++){
            glm::dvec3 rayDir = glm::normalize(camera.pixelToWorld( (double)j,(double)i) - camera.location);
            Ray ray = Ray(camera.location,rayDir,1);
            glm::dvec3 colorObtained = rayTrace(ray,objects,lightSources,1,4,glm::dvec3(0,0,0));
            // image[ i*width*3 + j*3 ]=(int)colorObtained[0]*255;
            // image[i*width*3 + j*3  +1 ]=(int)colorObtained[1]*255;
            // image[i*width*3 + j*3 + 2]=(int)colorObtained[2]*255;
            // myfile<<image[i*width*3 + j*3 ]<<","<<image[i*width*3 + j*3 +1]<<","<<image[i*width*3 + j*3 +2];
            // if( i!=(height-1) || (j!=width-1))myfile<<",";
            image[i][j][0]=(int) (colorObtained[0]*255);
            image[i][j][1]=(int) (colorObtained[1]*255);
            image[i][j][2]=(int) (colorObtained[2]*255);
        }
    }
    
    for(int i=0;i<height;i++){
        for(int j=0;j<height;j++){
            if (!(i==0 && j==0))myfile<<",";
            myfile<<image[i][j][0]<<","<<image[i][j][1]<<","<<image[i][j][2];
            
        }
    }
    myfile.close();
    
}



// }