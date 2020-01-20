#include "scene.h"
#include <glm/glm.hpp>

void createScene(std::vector<PointSource*>&lightSources,std::vector<PointSource*>&pointSources,std::vector<Cylinder*>&tubeLights,std::vector<Sphere*>&shinyBalls,std::vector<Sphere*>&snowSpheres,std::vector<Wall*>&walls,std::vector<Object*>&objects,double R,int width,int height){
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

    double diffCoeff1 = 0.25;
    double scale1 = 1;

    double diffCoeff2 = 0.25;
    double scale2 = 1;

    double roughness1 = 0.2;
    double roughness2 = 0.2;

    for(int i =0 ;i<6;i++){
        double angle1 = i * M_PI/3;
        double angle2 = angle1 + M_PI/6;
        
        glm::dvec3 loc1 = glm::dvec3( 2*R + circleRadius*cos(angle1), R/4, -2*R - circleRadius*sin(angle1));
        glm::dvec3 loc2 = glm::dvec3(2*R + circleRadius*cos(angle2),R/4, -2*R - circleRadius*sin(angle2));

        int id1 = 2*i;
        int id2 = 2*i+1;

        glm::dvec3 color1;
        // glm::dvec3 specColor1;

        glm::dvec3 color2;
        // glm::dvec3 specColor2;

        if(id1%3==0){
           color1 = glm::dvec3(0,1,1);
        //    color1 = color1;
        }
        else if(id1%3==1){
            color1 = glm::dvec3(1,165/255,0);
            // color1 = color1;
        }
        else{
            color1 = glm::dvec3(1,0,1);
            // color1 = color1;
        }


        if(id2%3==0){
           color2 = glm::dvec3(0,1,1);
        //    color2 = color2;
        }
        else if(id2%3==1){
            color2 = glm::dvec3(1,165/255,0);
            // color2 = color2;
        }
        else{
            color2 = glm::dvec3(1,0,1);
            // color2 = color2;
        }

        double dVal = 0.25;
        shinyBalls.push_back( new Sphere(id,loc1,color1,R/4,1.655,scale1,diffCoeff1,roughness1,kt_1,kr_1,dVal,0,true));
        id++;

        shinyBalls.push_back( new Sphere(id,loc2,color2,R/4,1.655,scale2,diffCoeff2,roughness2,kt_2,kr_2,dVal,0,true));
        id++;
    }

    glm::dvec3 snowColor = glm::dvec3(1,0.95,0.95);
    // glm::dvec3 snowSpecColor = glm::dvec3(1,1,1);
    double snowScale = 100;
    double snowdiffCoeff = 0.8;

    double snowRoughness = 1;
    
    double snowKtrans = 0.0;
    double snowKreflec = 0.1;


    
    double snowRefractiveIndex = 1.31;
    double snowDVal = 0.65;
    double radius1 = R;
    glm::dvec3 location1 = glm::dvec3(2*R,R,-2*R);
    Sphere* sphere1 = new Sphere(id,location1,snowColor,radius1,snowRefractiveIndex,snowScale,snowdiffCoeff,snowRoughness,snowKtrans,snowKreflec,snowDVal,0,true);
    id++;
    // cout<<"Sphere 1 id:"<<sphere1->getID()<<" kt:"<<sphere1->getK_Transmission()<<"\n\n";


    double radius2 = R/2;
    double polarCoordinateAngle2 = M_PI/3;
    // std::cout<<(radius2*sin(polarCoordinateAngle2) + sqrt(radius1*radius1 - radius2*radius2*cos(polarCoordinateAngle2)*cos(polarCoordinateAngle2)))/radius1<<"\n";
    glm::dvec3 location2 = location1 + glm::dvec3(0, (radius2*sin(polarCoordinateAngle2) + sqrt(radius1*radius1 - radius2*radius2*cos(polarCoordinateAngle2)*cos(polarCoordinateAngle2))),0);
    std::cout<<location2[1]/R<<"\n";
    Sphere* sphere2 = new Sphere(id,location2,snowColor,radius2,snowRefractiveIndex,snowScale,snowdiffCoeff,snowRoughness,snowKtrans,snowKreflec,snowDVal,0,true);
    id++;

    double radius3 = R/3;
    double polarCoordinateAngle3 = M_PI/3;
    std::cout<<"HI "<<(radius2*sin(polarCoordinateAngle3)+sqrt(radius3*radius3 - radius2*radius2*cos(polarCoordinateAngle3)*cos(polarCoordinateAngle3)))/radius2<<"\n";
    glm::dvec3 location3 = location2 + glm::dvec3(0,radius2*sin(polarCoordinateAngle3)+sqrt(radius3*radius3 - radius2*radius2*cos(polarCoordinateAngle3)*cos(polarCoordinateAngle3)),0);
    std::cout<<location3[1]/R<<"\n";
    
    Sphere* sphere3 = new Sphere(id,location3,snowColor,radius3,snowRefractiveIndex,snowScale,snowdiffCoeff,snowRoughness,snowKtrans,snowKreflec,snowDVal,0,true);
    id++;

    bool seeWalls = false;
    glm::dvec3 sideWallColor = glm::dvec3(1,0,0);
    // glm::dvec3 sideWallSpecColor = glm::dvec3(1,0,0);
    double sideWallScale = 0;
    double sideWallDiffuseCoeff = 0.1;
    double sideWallKtrans = 0;
    double sideWallKreflec = 0.1;
    double sideWallRoughness = 0.8;
    double sideWallDVal = 1;
    std::vector<glm::dvec3> cornersLeft;
    cornersLeft.push_back(glm::dvec3(0,0,0));
    cornersLeft.push_back(glm::dvec3(0,4*R,0));
    cornersLeft.push_back(glm::dvec3(0,4*R,-4*R));
    cornersLeft.push_back(glm::dvec3(0,0,-4*R));
    

    Wall* leftWall = new Wall(id,cornersLeft,cornersLeft[0],sideWallColor,1.1,sideWallScale,sideWallDiffuseCoeff,sideWallRoughness,sideWallKtrans,sideWallKreflec,sideWallDVal,1,seeWalls);
    id++;



    std::vector<glm::dvec3> cornersRight;
    cornersRight.push_back(glm::dvec3(4*R,0,0));
    cornersRight.push_back(glm::dvec3(4*R,4*R,0));
    cornersRight.push_back(glm::dvec3(4*R,4*R,-4*R));
    cornersRight.push_back(glm::dvec3(4*R,0,-4*R));
    
    Wall* rightWall = new Wall(id,cornersRight,cornersRight[0],sideWallColor,1.1,sideWallScale,sideWallDiffuseCoeff,sideWallRoughness,sideWallKtrans,sideWallKreflec,sideWallDVal,1,seeWalls);
    id++;

    

    glm::dvec3 ceilWallColor = glm::dvec3(0,1,0);
    // glm::dvec3 ceilWallSpecColor = glm::dvec3(0,1,0);
    double ceilWallScale = 0;
    double ceilWallDiffuseCoeff = 0.1;
    double ceilWallKtrans = 0;
    double ceilWallKreflec = 0.1;
    double ceilWallRoughness = 0.8;
    double ceilWallDVal = 1;

    std::vector<glm::dvec3> cornersCeil;
    cornersCeil.push_back(glm::dvec3(0,4*R,0));
    cornersCeil.push_back(glm::dvec3(4*R,4*R,0));
    cornersCeil.push_back(glm::dvec3(4*R,4*R,-4*R));
    cornersCeil.push_back(glm::dvec3(0,4*R,-4*R));
    
    Wall* ceilWall = new Wall(id,cornersCeil,cornersCeil[0],ceilWallColor,1.1,ceilWallScale,ceilWallDiffuseCoeff,ceilWallRoughness,ceilWallKtrans,ceilWallKreflec,ceilWallDVal,1,seeWalls);
    id++;

    glm::dvec3 bottomWallColor = glm::dvec3(1,1,1);
    // glm::dvec3 bottomWallSpecColor = glm::dvec3(1,1,1);
    double bottomWallScale = 0;
    double bottomWallDiffuseCoeff = 0.1;
    double bottomWallKtrans = 0;
    double bottomWallKreflec = 0.1;
    double bottomWallRoughness = 0.8;
    double bottomWallDVal = 1;

    
    std::vector<glm::dvec3> cornersBottom;
    cornersBottom.push_back(glm::dvec3(0,0,0));
    cornersBottom.push_back(glm::dvec3(4*R,0,0));
    cornersBottom.push_back(glm::dvec3(4*R,0,-4*R));
    cornersBottom.push_back(glm::dvec3(0,0,-4*R));

    Wall* bottomWall = new Wall(id,cornersBottom,cornersBottom[0],bottomWallColor,1.1,bottomWallScale,bottomWallDiffuseCoeff,bottomWallRoughness,bottomWallKtrans,bottomWallKreflec,bottomWallDVal,1,seeWalls);
    id++;

    glm::dvec3 farWallColor = glm::dvec3(0,0,0);
    // glm::dvec3 farWallSpecColor = glm::dvec3(1,0,0);
    double farWallScale = 0.1;
    double farWallDiffuseCoeff = 0;
    double farWallKtrans = 0;
    double farWallKreflec = 0.1;
    double farWallRoughness = 0.8;
    double farWallDVal = 0;


    std::vector<glm::dvec3> cornersFar;
    cornersFar.push_back(glm::dvec3(0,0,-4*R));
    cornersFar.push_back(glm::dvec3(4*R,0,-4*R));
    cornersFar.push_back(glm::dvec3(4*R,4*R,-4*R));
    cornersFar.push_back(glm::dvec3(0,4*R,-4*R));
    
    Wall* farWall = new Wall(id,cornersFar,cornersFar[0],farWallColor,1.1,farWallScale,farWallDiffuseCoeff,farWallRoughness,farWallKtrans,farWallKreflec,farWallDVal,1,seeWalls);
    id++;
    double cylinderRadius = R/25;
    double cylinderHeight = R;
    glm::dvec3 cylinderColor = glm::dvec3(1,1,1);
    double cylinderRefrac = 1.1;
    // glm::dvec3 cylinderSpecColour = glm::dvec3(1,1,1);
    double cylinderScale=1;
    double cylinderDiffCoeff=1;
    double cylinderRoughness=1;
    double cylinderK_trans=1;
    double cylinderK_reflec=0;
    int cylinderType = 2;
    bool cylinderVisibility = true;
    double cylinderDVal = 1;

    
    glm::dvec3 tubeLightColor = glm::dvec3(0.5,0.5,0.5);
    double tubeLightAttenuation = 0.001;
    double tubeLightAmbientCoefficient = 0.01;
    
    glm::dvec3 cylinderRef1 = glm::dvec3(0.01*R,R*0.5,0);
    Cylinder * cylinder1 = new Cylinder(id,tubeLightColor,tubeLightAttenuation,tubeLightAmbientCoefficient,xyz,cylinderRef1,cylinderRadius,cylinderColor,cylinderHeight,cylinderRefrac,cylinderScale,cylinderDiffCoeff,cylinderRoughness,cylinderK_trans,cylinderK_reflec,cylinderDVal,cylinderType,cylinderVisibility);
    id++;
    

    glm::dvec3 cylinderRef2 = glm::dvec3(3.99*R,R*0.5,0);
    Cylinder * cylinder2 = new Cylinder(id,tubeLightColor,tubeLightAttenuation,tubeLightAmbientCoefficient,xyz,cylinderRef2,cylinderRadius,cylinderColor,cylinderHeight,cylinderRefrac,cylinderScale,cylinderDiffCoeff,cylinderRoughness,cylinderK_trans,cylinderK_reflec,cylinderDVal,cylinderType,cylinderVisibility);
    id++;


    glm::dvec3 cylinderRef3 = glm::dvec3(3.99*R,R*0.5,-3.99*R);
    Cylinder * cylinder3 = new Cylinder(id,tubeLightColor,tubeLightAttenuation,tubeLightAmbientCoefficient,xyz,cylinderRef3,cylinderRadius,cylinderColor,cylinderHeight,cylinderRefrac,cylinderScale,cylinderDiffCoeff,cylinderRoughness,cylinderK_trans,cylinderK_reflec,cylinderDVal,cylinderType,cylinderVisibility);
    id++;


    glm::dvec3 cylinderRef4 = glm::dvec3(0,R*0.5,-3.99*R);
    Cylinder * cylinder4 = new Cylinder(id,tubeLightColor,tubeLightAttenuation,tubeLightAmbientCoefficient,xyz,cylinderRef4,cylinderRadius,cylinderColor,cylinderHeight,cylinderRefrac,cylinderScale,cylinderDiffCoeff,cylinderRoughness,cylinderK_trans,cylinderK_reflec,cylinderDVal,cylinderType,cylinderVisibility);
    id++;
                            
    snowSpheres.push_back(sphere1);
    snowSpheres.push_back(sphere2);
    snowSpheres.push_back(sphere3);
    walls.push_back(farWall);
    walls.push_back(leftWall);
    walls.push_back(rightWall);
    walls.push_back(ceilWall);
    walls.push_back(bottomWall);
    tubeLights.push_back(cylinder1);
    tubeLights.push_back(cylinder2);
    tubeLights.push_back(cylinder3);
    tubeLights.push_back(cylinder4);


    
    for(int i =0;i<(int)(shinyBalls.size());i++)objects.push_back(shinyBalls[i]);
    for(int i = 0;i<(int)(walls.size());i++)objects.push_back(walls[i]);
    for(int i =0;i<(int)snowSpheres.size();i++)objects.push_back(snowSpheres[i]);
    for(int i = 0;i<(int)tubeLights.size();i++)objects.push_back(tubeLights[i]);

    // pointSources.push_back(source1);
    // pointSources.push_back(source2);
    // pointSources.push_back(source3);
    // pointSources.push_back(source4);


    for(int i =0;i<(int) pointSources.size();i++){
        lightSources.push_back(pointSources[i]);
    }
    for(int i = 0;i<(int)tubeLights.size();i++){
        std::vector<PointSource*> points = tubeLights[i]->getPointSources();
        for(int j = 0;j<(int)points.size();j++){
            lightSources.push_back(points[j]);
        }
    }    

    
    // std::cout<<lightSources.size()<<"\n";
    
}