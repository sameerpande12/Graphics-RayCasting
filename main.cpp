#include <iostream>
#include "Ray.h"
#include "PointSource.h"
#include "Sphere.h"
#include "Box.h"
#include "Camera.h"
#include "Object.h"
#include <glm/glm.hpp>
#include <fstream>
#include "Wall.h"
#include "omp.h"
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
    
    glm::dvec3 cameraPosition = glm::dvec3(2*R,2*R,0.5*R);
    Camera camera = Camera(cameraPosition,xyz,width,height,M_PI/2);


    glm::dvec3 lightSourceLocation1 = glm::dvec3(0.01*R,3.99*R,-0.01*R);
    glm::dvec3 lightSourceIntensity1 = glm::dvec3(1,1,1);
    double attenuation1 = 0.001;
    double ambientCoefficient1 = 0.1;
    PointSource source1 = PointSource(lightSourceLocation1,lightSourceIntensity1,attenuation1,ambientCoefficient1);




    glm::dvec3 lightSourceLocation2 = glm::dvec3(0.01*R,3.99*R,-3.99*R);
    glm::dvec3 lightSourceIntensity2 = glm::dvec3(1,1,1);
    double attenuation2 = 0.01;
    double ambientCoefficient2 = 0.1;
    PointSource source2 = PointSource(lightSourceLocation2,lightSourceIntensity2,attenuation2,ambientCoefficient2);
    
    

    glm::dvec3 lightSourceLocation3 = glm::dvec3(3.99*R,3.99*R,-0.01*R);
    glm::dvec3 lightSourceIntensity3 = glm::dvec3(1,1,1);
    double attenuation3 = 0.01;
    double ambientCoefficient3 = 0.1;
    PointSource source3 = PointSource(lightSourceLocation3,lightSourceIntensity3,attenuation3,ambientCoefficient3);


    glm::dvec3 lightSourceLocation4 = glm::dvec3(3.99*R,3.99*R,-3.99*R);
    glm::dvec3 lightSourceIntensity4 = glm::dvec3(1,1,1);
    double attenuation4 = 0.01;
    double ambientCoefficient4 = 0.1;
    PointSource source4 = PointSource(lightSourceLocation4,lightSourceIntensity4,attenuation4,ambientCoefficient4);

    glm::dvec3 snowColor = glm::dvec3(1,0.98,0.98);
    glm::dvec3 snowSpecColor = glm::dvec3(1,1,1);
    double snowSpecCoeff = 0.035;
    double snowdiffCoeff = 0.065;

    double snowShininess = 0;
    
    double snowKtrans = 0;
    double snowKreflec = 0;



    double radius1 = R;
    glm::dvec3 location1 = glm::dvec3(2*R,R,-2*R);
    Sphere* sphere1 = new Sphere(id,location1,snowColor,radius1,1.1,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec);
    id++;


    glm::dvec3 location2 = glm::dvec3(2*R,2.25*R,-2*R);
    double radius2 = R/2;
    Sphere* sphere2 = new Sphere(id,location2,snowColor,radius2,1.1,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec);
    id++;

    
    glm::dvec3 location3 = glm::dvec3(2*R,2.7*R,-2*R);
    double radius3 = R/4;
    Sphere* sphere3 = new Sphere(id,location3,snowColor,radius3,1.1,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec);
    id++;


    glm::dvec3 sideWallColor = glm::dvec3(1,0,0);
    glm::dvec3 sideWallSpecColor = glm::dvec3(1,0,0);
    double sideWallSpecCoeff = 0;
    double sideWallDiffuseCoeff = 0.1;
    double sideWallKtrans = 0;
    double sideWallKreflec = 0.1;
    double sideWallShininess = 0;

    glm::dvec4 sideWallParam1 = glm::dvec4(1,0,0,0);
    Wall* leftWall = new Wall(id,glm::dvec3(0,0,0),sideWallColor,sideWallParam1,1.1,sideWallSpecColor,sideWallSpecCoeff,sideWallDiffuseCoeff,sideWallShininess,sideWallKtrans,sideWallKreflec);
    id++;

    glm::dvec4 sideWallParam2 = glm::dvec4(1,0,0,4*R);
    Wall* rightWall = new Wall(id,glm::dvec3(4*R,0,0),sideWallColor,sideWallParam2,1.1,sideWallSpecColor,sideWallSpecCoeff,sideWallDiffuseCoeff,sideWallShininess,sideWallKtrans,sideWallKreflec);
    id++;


    glm::dvec3 ceilWallColor = glm::dvec3(0,1,0);
    glm::dvec3 ceilWallSpecColor = glm::dvec3(0,1,0);
    double ceilWallSpecCoeff = 0;
    double ceilWallDiffuseCoeff = 0.1;
    double ceilWallKtrans = 0;
    double ceilWallKreflec = 0.1;
    double ceilWallShininess = 0;

    glm::dvec4 ceilWallParam1 = glm::dvec4(0,1,0,4*R);
    Wall* ceilWall = new Wall(id,glm::dvec3(0,2*R,0),ceilWallColor,ceilWallParam1,1.1,ceilWallSpecColor,ceilWallSpecCoeff,ceilWallDiffuseCoeff,ceilWallShininess,ceilWallKtrans,ceilWallKreflec);
    id++;

    glm::dvec3 bottomWallColor = glm::dvec3(1,1,1);
    glm::dvec3 bottomWallSpecColor = glm::dvec3(1,1,1);
    double bottomWallSpecCoeff = 0;
    double bottomWallDiffuseCoeff = 0.1;
    double bottomWallKtrans = 0;
    double bottomWallKreflec = 0.1;
    double bottomWallShininess = 0;

    glm::dvec4 bottomWallParam1 = glm::dvec4(0,1,0,0);
    Wall* bottomWall = new Wall(id,glm::dvec3(0,0,0),bottomWallColor,bottomWallParam1,1.1,bottomWallSpecColor,bottomWallSpecCoeff,bottomWallDiffuseCoeff,bottomWallShininess,bottomWallKtrans,bottomWallKreflec);
    id++;

    glm::dvec3 farWallColor = glm::dvec3(0,0,0);
    glm::dvec3 farWallSpecColor = glm::dvec3(1,0,0);
    double farWallSpecCoeff = 0.1;
    double farWallDiffuseCoeff = 0;
    double farWallKtrans = 0;
    double farWallKreflec = 0.1;
    double farWallShininess = 0.5;

    glm::dvec4 farWallParam1 = glm::dvec4(0,0,1,-4*R);
    Wall* farWall = new Wall(id,glm::dvec3(0,0,-R*4),farWallColor,farWallParam1,1.1,farWallSpecColor,farWallSpecCoeff,farWallDiffuseCoeff,farWallShininess,farWallKtrans,farWallKreflec);
    id++;
    std::vector<Object*> objects;
    std::vector<PointSource> lightSources;

    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);
    objects.push_back(farWall);
    objects.push_back(leftWall);
    objects.push_back(rightWall);
    objects.push_back(ceilWall);
    objects.push_back(bottomWall);

    lightSources.push_back(source1);
    lightSources.push_back(source2);
    lightSources.push_back(source3);
    lightSources.push_back(source4);
    
    std::ofstream myfile;
    myfile.open("image.csv");
    double start = omp_get_wtime();
    #pragma omp parallel
    {   
        #pragma omp for
        for(int iter = 0;iter<height*width;iter++){
                int i,j;
                i = iter/width;
                j = iter%width;
        
                glm::dvec3 rayDir = glm::normalize(camera.pixelToWorld( (double)j,(double)i) - camera.location);
                Ray ray = Ray(camera.location,rayDir,1);
                glm::dvec3 colorObtained = rayTrace(ray,objects,lightSources,1,4,glm::dvec3(0,0,0));
        
                image[i][j][0]=(int) (colorObtained[0]*255);
                image[i][j][1]=(int) (colorObtained[1]*255);
                image[i][j][2]=(int) (colorObtained[2]*255);
        
        }
    }
    double end = omp_get_wtime();
    cout<<end-start<<endl;
    
    for(int i=0;i<height;i++){
        for(int j=0;j<height;j++){
            if (!(i==0 && j==0))myfile<<",";
            myfile<<image[i][j][0]<<","<<image[i][j][1]<<","<<image[i][j][2];
            
        }
    }
    myfile.close();
    
}



// }