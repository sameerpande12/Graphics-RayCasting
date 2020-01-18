#include "scene.h"
#include <glm/glm.hpp>

void createScene(std::vector<PointSource*>&lightSources,std::vector<Sphere*>&shinyBalls,std::vector<Sphere*>&snowSpheres,std::vector<Wall*>&walls,std::vector<Object*>&objects,double R,int width,int height){
    Axes xyz = Axes();
    double circleRadius = 1.5*R;
    int id = 1;
    
    xyz.setAxes(glm::dvec3(1,0,0),glm::dvec3(0,1,0),glm::dvec3(0,0,1));
    


    glm::dvec3 lightSourceLocation1 = glm::dvec3(0.01*R,3.99*R,-0.01*R);
    glm::dvec3 lightSourceIntensity1 = glm::dvec3(1,1,1);
    double attenuation1 = 0.001;
    double ambientCoefficient1 = 0.1;
    PointSource* source1 = new PointSource(lightSourceLocation1,lightSourceIntensity1,attenuation1,ambientCoefficient1);




    glm::dvec3 lightSourceLocation2 = glm::dvec3(0.01*R,3.99*R,-3.99*R);
    glm::dvec3 lightSourceIntensity2 = glm::dvec3(1,1,1);
    double attenuation2 = 0.01;
    double ambientCoefficient2 = 0.1;
    PointSource* source2 = new PointSource(lightSourceLocation2,lightSourceIntensity2,attenuation2,ambientCoefficient2);
    
    

    glm::dvec3 lightSourceLocation3 = glm::dvec3(3.99*R,3.99*R,-0.01*R);
    glm::dvec3 lightSourceIntensity3 = glm::dvec3(1,1,1);
    double attenuation3 = 0.01;
    double ambientCoefficient3 = 0.1;
    PointSource* source3 = new PointSource(lightSourceLocation3,lightSourceIntensity3,attenuation3,ambientCoefficient3);


    glm::dvec3 lightSourceLocation4 = glm::dvec3(3.99*R,3.99*R,-3.99*R);
    glm::dvec3 lightSourceIntensity4 = glm::dvec3(1,1,1);
    double attenuation4 = 0.01;
    double ambientCoefficient4 = 0.1;
    PointSource* source4 = new PointSource(lightSourceLocation4,lightSourceIntensity4,attenuation4,ambientCoefficient4);
    
    
    double kt_1 = .6;
    double kr_1 = .3;

    double kt_2 = 0;
    double kr_2 = 0.9;

    double diffCoeff1 = 0.025;
    double specCoeff1 = 0.075;

    double diffCoeff2 = 0.025;
    double specCoeff2 = 0.075;

    double shininess1 = 0.8;
    double shininess2 = 0.8;

    for(int i =0 ;i<6;i++){
        double angle1 = i * M_PI/3;
        double angle2 = angle1 + M_PI/6;
        
        glm::dvec3 loc1 = glm::dvec3( 2*R + circleRadius*cos(angle1), R/4, -2*R - circleRadius*sin(angle1));
        glm::dvec3 loc2 = glm::dvec3(2*R + circleRadius*cos(angle2),R/4, -2*R - circleRadius*sin(angle2));

        int id1 = 2*i;
        int id2 = 2*i+1;

        glm::dvec3 color1;
        glm::dvec3 specColor1;

        glm::dvec3 color2;
        glm::dvec3 specColor2;

        if(id1%3==0){
           specColor1 = glm::dvec3(0,1,1);
           color1 = specColor1;
        }
        else if(id1%3==1){
            specColor1 = glm::dvec3(1,165/255,0);
            color1 = specColor1;
        }
        else{
            specColor1 = glm::dvec3(1,0,1);
            color1 = specColor1;
        }


        if(id2%3==0){
           specColor2 = glm::dvec3(0,1,1);
           color2 = specColor2;
        }
        else if(id2%3==1){
            specColor2 = glm::dvec3(1,165/255,0);
            color2 = specColor2;
        }
        else{
            specColor2 = glm::dvec3(1,0,1);
            color2 = specColor2;
        }

        shinyBalls.push_back( new Sphere(id,loc1,color1,R/4,1.5,specColor1,specCoeff1,diffCoeff1,shininess1,kt_1,kr_1,0,true));
        id++;

        shinyBalls.push_back( new Sphere(id,loc2,color2,R/4,1.5,specColor2,specCoeff2,diffCoeff2,shininess2,kt_2,kr_2,0,true));
        id++;
    }

    glm::dvec3 snowColor = glm::dvec3(1,0.98,0.98);
    glm::dvec3 snowSpecColor = glm::dvec3(1,1,1);
    double snowSpecCoeff = 0.035;
    double snowdiffCoeff = 0.065;

    double snowShininess = 0;
    
    double snowKtrans = 0.0;
    double snowKreflec = 0.09;


    
    double snowRefractiveIndex = 1.2;

    double radius1 = R;
    glm::dvec3 location1 = glm::dvec3(2*R,R,-2*R);
    Sphere* sphere1 = new Sphere(id,location1,snowColor,radius1,snowRefractiveIndex,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec,0,true);
    id++;
    // cout<<"Sphere 1 id:"<<sphere1->getID()<<" kt:"<<sphere1->getK_Transmission()<<"\n\n";


    glm::dvec3 location2 = glm::dvec3(2*R,2.25*R,-2*R);
    double radius2 = R/2;
    Sphere* sphere2 = new Sphere(id,location2,snowColor,radius2,snowRefractiveIndex,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec,0,true);
    id++;

    
    glm::dvec3 location3 = glm::dvec3(2*R,2.7*R,-2*R);
    double radius3 = R/4;
    Sphere* sphere3 = new Sphere(id,location3,snowColor,radius3,snowRefractiveIndex,snowSpecColor,snowSpecCoeff,snowdiffCoeff,snowShininess,snowKtrans,snowKreflec,0,true);
    id++;


    glm::dvec3 sideWallColor = glm::dvec3(1,0,0);
    glm::dvec3 sideWallSpecColor = glm::dvec3(1,0,0);
    double sideWallSpecCoeff = 0;
    double sideWallDiffuseCoeff = 0.1;
    double sideWallKtrans = 0;
    double sideWallKreflec = 0.1;
    double sideWallShininess = 0;

    std::vector<glm::dvec3> cornersLeft;
    cornersLeft.push_back(glm::dvec3(0,0,0));
    cornersLeft.push_back(glm::dvec3(0,4*R,0));
    cornersLeft.push_back(glm::dvec3(0,4*R,-4*R));
    cornersLeft.push_back(glm::dvec3(0,0,-4*R));

    Wall* leftWall = new Wall(id,cornersLeft,cornersLeft[0],sideWallColor,1.1,sideWallSpecColor,sideWallSpecCoeff,sideWallDiffuseCoeff,sideWallShininess,sideWallKtrans,sideWallKreflec,1,true);
    id++;



    std::vector<glm::dvec3> cornersRight;
    cornersRight.push_back(glm::dvec3(4*R,0,0));
    cornersRight.push_back(glm::dvec3(4*R,4*R,0));
    cornersRight.push_back(glm::dvec3(4*R,4*R,-4*R));
    cornersRight.push_back(glm::dvec3(4*R,0,-4*R));
    
    Wall* rightWall = new Wall(id,cornersRight,cornersRight[0],sideWallColor,1.1,sideWallSpecColor,sideWallSpecCoeff,sideWallDiffuseCoeff,sideWallShininess,sideWallKtrans,sideWallKreflec,1,true);
    id++;

    

    glm::dvec3 ceilWallColor = glm::dvec3(0,1,0);
    glm::dvec3 ceilWallSpecColor = glm::dvec3(0,1,0);
    double ceilWallSpecCoeff = 0;
    double ceilWallDiffuseCoeff = 0.1;
    double ceilWallKtrans = 0;
    double ceilWallKreflec = 0.1;
    double ceilWallShininess = 0;


    std::vector<glm::dvec3> cornersCeil;
    cornersCeil.push_back(glm::dvec3(0,4*R,0));
    cornersCeil.push_back(glm::dvec3(4*R,4*R,0));
    cornersCeil.push_back(glm::dvec3(4*R,4*R,-4*R));
    cornersCeil.push_back(glm::dvec3(0,4*R,-4*R));
    
    Wall* ceilWall = new Wall(id,cornersCeil,cornersCeil[0],ceilWallColor,1.1,ceilWallSpecColor,ceilWallSpecCoeff,ceilWallDiffuseCoeff,ceilWallShininess,ceilWallKtrans,ceilWallKreflec,1,true);
    id++;

    glm::dvec3 bottomWallColor = glm::dvec3(1,1,1);
    glm::dvec3 bottomWallSpecColor = glm::dvec3(1,1,1);
    double bottomWallSpecCoeff = 0;
    double bottomWallDiffuseCoeff = 0.1;
    double bottomWallKtrans = 0;
    double bottomWallKreflec = 0.1;
    double bottomWallShininess = 0;


    
    std::vector<glm::dvec3> cornersBottom;
    cornersBottom.push_back(glm::dvec3(0,0,0));
    cornersBottom.push_back(glm::dvec3(4*R,0,0));
    cornersBottom.push_back(glm::dvec3(4*R,0,-4*R));
    cornersBottom.push_back(glm::dvec3(0,0,-4*R));

    Wall* bottomWall = new Wall(id,cornersBottom,cornersBottom[0],bottomWallColor,1.1,bottomWallSpecColor,bottomWallSpecCoeff,bottomWallDiffuseCoeff,bottomWallShininess,bottomWallKtrans,bottomWallKreflec,1,true);
    id++;

    glm::dvec3 farWallColor = glm::dvec3(0,0,0);
    glm::dvec3 farWallSpecColor = glm::dvec3(1,0,0);
    double farWallSpecCoeff = 0.1;
    double farWallDiffuseCoeff = 0;
    double farWallKtrans = 0;
    double farWallKreflec = 0.1;
    double farWallShininess = 0.5;


    std::vector<glm::dvec3> cornersFar;
    cornersFar.push_back(glm::dvec3(0,0,-4*R));
    cornersFar.push_back(glm::dvec3(4*R,0,-4*R));
    cornersFar.push_back(glm::dvec3(4*R,4*R,-4*R));
    cornersFar.push_back(glm::dvec3(0,4*R,-4*R));
    
    Wall* farWall = new Wall(id,cornersFar,cornersFar[0],farWallColor,1.1,farWallSpecColor,farWallSpecCoeff,farWallDiffuseCoeff,farWallShininess,farWallKtrans,farWallKreflec,1,true);
    id++;
    

    snowSpheres.push_back(sphere1);
    snowSpheres.push_back(sphere2);
    snowSpheres.push_back(sphere3);
    walls.push_back(farWall);
    walls.push_back(leftWall);
    walls.push_back(rightWall);
    walls.push_back(ceilWall);
    walls.push_back(bottomWall);

    for(int i =0;i<(int)(shinyBalls.size());i++)objects.push_back(shinyBalls[i]);
    for(int i = 0;i<(int)(walls.size());i++)objects.push_back(walls[i]);
    for(int i =0;i<(int)snowSpheres.size();i++)objects.push_back(snowSpheres[i]);
    lightSources.push_back(source1);
    lightSources.push_back(source2);
    lightSources.push_back(source3);
    lightSources.push_back(source4);
    
}