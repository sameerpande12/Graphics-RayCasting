#include <iostream>
#include "Ray.h"
#include "PointSource.h"
#include "Sphere.h"
#include "Box.h"
#include "Camera.h"
#include "Object.h"
#include <glm/glm.hpp>
#include <fstream>

int main(){

    double R = 5;
    Axes xyz = Axes();
    int width = 640;
    int height = 640;
    int id = 1;

    xyz.setAxes(glm::dvec3(1,0,0),glm::dvec3(0,1,0),glm::dvec3(0,0,1));


    Camera camera = Camera(glm::dvec3(2*R,2*R,0),xyz,640,640,M_PI/2);

    double image[width][height][3];

    glm::dvec3 snowColor = glm::dvec3(1,0.98,0.98);
    glm::dvec3 location = glm::dvec3(2*R,2*R,-2*R);
    glm::dvec3 snowSpecColor = glm::dvec3(0,0,0);
    double snowSpecCoeff = 0;

    double snowShininess = 0.3;
    double snowdiffCoeff = 1;
    double snowKtrans = 0;
    double snowKreflec = 1;
    Sphere* sphere = new Sphere(id,location,snowColor,R,1.1,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec);

    glm::dvec3 lightSourceLocation = glm::dvec3(0,1.99*R,-0.01*R);
    glm::dvec3 lightSourceIntensity = glm::dvec3(1,1,1);
    double attenuation = 0.01;
    double ambientCoefficient = 0.4;
    PointSource source = PointSource(lightSourceLocation,lightSourceIntensity,attenuation,ambientCoefficient);


    std::vector<Object*> objects;
    std::vector<PointSource> lightSources;

    objects.push_back(sphere);
    lightSources.push_back(source);

    std::ofstream myfile;
    myfile.open("image.csv");
    
    for(int i = 0;i<width;i++){
        for(int j=0;j<height;j++){
            glm::dvec3 rayDir = glm::normalize(camera.pixelToWorld( (double)i,(double)j) - camera.location);
            Ray ray = Ray(camera.location,rayDir,1);
            glm::dvec3 colorObtained = rayTrace(ray,objects,lightSources,1,1,glm::dvec3(0,0,0));
            image[i][j][0]=(int)colorObtained[0]*255;
            image[i][j][1]=(int)colorObtained[1]*255;
            image[i][j][2]=(int)colorObtained[2]*255;
            myfile<<image[i][j][0]<<"\n"<<image[i][j][1]<<"\n"<<image[i][j][2]<<"\n";
        }
    }

    
    
}



// }