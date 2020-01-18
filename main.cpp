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
#include "OpenGLdraw.h"
#define cout std::cout
#define endl std::endl

void keyCallback(GLFWwindow* window,int key, int scancode,int action,int mods);

#define QUIT(m,v)      { fprintf(stderr, "%s:%s\n", m, v); exit(1); }
Camera camera;
int toggleValue = 0;
std::vector<Object*> shinyBalls;
std::vector<Wall*> walls;
std::vector<Object*> snowSpheres;
std::vector<Object*> objects;
std::vector<PointSource*> lightSources;

double R = 5;
double circleRadius = 1.5*R;
glm::dvec3 centreOfRoom = glm::dvec3(2*R,2*R,-2*R);
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void printAxes(Axes ax){
    
    for(int i = 0;i<3;i++){
        glm::dvec3 axis = ax.getAxis(i);
        cout<<"(";
        for(int j=0;j<3;j++){
            cout<<axis[j];
            if(j<2)cout<<",";
        }
        cout<<") ";
    }
}

int main(int argc,char*argv[]){

    int WIDTH = std::stoi(argv[1]);//requested WIDTH
    int HEIGHT = std::stoi(argv[2]);//requested HEIGHT
    

    if (!glfwInit())
        QUIT("gWindow_GLFW", "Could not Initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwSetErrorCallback(error_callback);

    bool coreProfile = true;
    if(coreProfile) {
       glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__ 
       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
   }

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "main", NULL, NULL);
    if (!window) {
        glfwTerminate();
        QUIT("gWindow_GLFW", "Could not create Window");
    }

    glfwMakeContextCurrent(window);

    if ( GLEW_OK != glewInit() ) {
        glfwTerminate();
        QUIT("gWindow_GLFW","glewInit failed");
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window,keyCallback);

    int width,height;
    glfwGetFramebufferSize(window, &width, &height);//save the alloted width and height
    glEnable(GL_TEXTURE_2D);
    OpenGLdraw opengl;
    opengl.init(width, height);
   

    
    GLubyte image[height*width*3];
    
    
    Axes xyz = Axes();
    
    int id = 1;
    // omp_set_num_threads(8);
    xyz.setAxes(glm::dvec3(1,0,0),glm::dvec3(0,1,0),glm::dvec3(0,0,1));
    
    glm::dvec3 cameraPosition = glm::dvec3(2*R,2*R,4*R);
    
    camera.location = cameraPosition;
    camera.axes = xyz;
    camera.width = width;
    camera.height = height;
    camera.fov = M_PI_2;


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
    
    while(!glfwWindowShouldClose(window)){   
        glfwPollEvents();//added to avoid glfw from thinking that window is not responding
        
        #pragma omp parallel for
        for(int iter = 0;iter<height*width;iter++){
                int i,j;
                i = iter/width;
                j = iter%width;
                
        
                glm::dvec3 rayDir = glm::normalize(camera.pixelToWorld( (double)j,(double)i) - camera.location);
                Ray ray = Ray(camera.location,rayDir,1);
                glm::dvec3 colorObtained = rayTrace(ray,objects,lightSources,1,4,glm::dvec3(0,0,0));
        
                image[iter*3]=(GLubyte) (colorObtained[0]*255);
                image[iter*3+1]=(GLubyte) (colorObtained[1]*255);
                image[iter*3+2]=(GLubyte) (colorObtained[2]*255);
                
        
        }
        glClearColor(0.5,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);
        opengl.draw(image,width,height,0,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    
}

void keyCallback(GLFWwindow* window,int key, int scancode,int action,int mods){

    if(key == GLFW_KEY_T && action == GLFW_PRESS){
        toggleValue = (toggleValue+1)%3;
        cout<<"Key t is pressed. t ="<<toggleValue<<endl;

    }
    else if(toggleValue == 0){//rotate entire scene
        if( (key==GLFW_KEY_UP || key==GLFW_KEY_DOWN) && action==GLFW_PRESS ){
            double angle = M_PI_4/3;//15 degrees
            if(key==GLFW_KEY_UP)angle = -angle;
            
            // camera.axes = rotateAxes(camera.axes,angle,0);
            // cout<<"New camera axes are-> ";
            // printAxes(camera.axes);
            // cout<<'\n';

            for(int i = 0;i<(int)shinyBalls.size();i++){//rotate about x axis
                glm::dvec3 relativePosition = shinyBalls[i]->getReference() - centreOfRoom;
                double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
                newPos[0] = shinyBalls[i]->getReference()[0];
                shinyBalls[i]->setReference(  newPos );
            }


            for(int i = 0;i<(int)walls.size();i++){
                std::vector<glm::dvec3>cornerPoints = walls[i]->getPoints();

                for(int j = 0;j<(int)cornerPoints.size();j++){//rotate about x axis
                    glm::dvec3 relativePosition = cornerPoints[j] - centreOfRoom;
                    double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
                    double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                    glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
                    newPos[0] = cornerPoints[j][0];
                    cornerPoints[j]=newPos;
                }
                walls[i]->updatePoints(cornerPoints);

            }


            for(int i = 0;i<(int)snowSpheres.size();i++){//rotate about x axis
                glm::dvec3 relativePosition = snowSpheres[i]->getReference() - centreOfRoom;
                double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
                newPos[0] = snowSpheres[i]->getReference()[0];
                snowSpheres[i]->setReference(  newPos );
            }

            for(int i = 0;i<(int)lightSources.size();i++){
                //rotate about x axis
                glm::dvec3 relativePosition = lightSources[i]->position - centreOfRoom;
                double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
                newPos[0] = lightSources[i]->position[0];
                lightSources[i]->position = newPos;
            }




        }
        else if((key==GLFW_KEY_LEFT || key==GLFW_KEY_RIGHT) && action==GLFW_PRESS){
            double angle = M_PI_4/3;
            if(key==GLFW_KEY_RIGHT)angle = -angle;
            for(int i = 0;i<(int)shinyBalls.size();i++){
                glm::dvec3 relativePosition = shinyBalls[i]->getReference() - centreOfRoom;
                double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                newPos[1] = shinyBalls[i]->getReference()[1];
                shinyBalls[i]->setReference(  newPos );
            }

            for(int i = 0;i<(int)lightSources.size();i++){
                glm::dvec3 relativePosition = lightSources[i]->position - centreOfRoom;
                double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                newPos[1] = lightSources[i]->position[1];
                lightSources[i]->position = newPos;
            }

            for(int i = 0;i<(int)walls.size();i++){
                std::vector<glm::dvec3>cornerPoints = walls[i]->getPoints();

                for(int j = 0;j<(int)cornerPoints.size();j++){
                    glm::dvec3 relativePosition = cornerPoints[j] - centreOfRoom;
                    double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                    double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                    glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                    newPos[1] = cornerPoints[j][1];
                    cornerPoints[j]=newPos;
                }
                walls[i]->updatePoints(cornerPoints);

            }
        }
        
    }
    else if(toggleValue == 1){//rotate only shiny balls
      if( (key==GLFW_KEY_LEFT || key==GLFW_KEY_RIGHT) && action==GLFW_PRESS){//rotate the shiny balls

        
        // (cos(a) + i sin(a))*(x + iz) = (cos(a)*x - sin(a)z)+i(cos(a)*z + sin(a)*x);
        double angle =  M_PI_4/3;//15 degrees
        if(key==GLFW_KEY_RIGHT)angle = -angle; 
        for(int i = 0;i<(int)shinyBalls.size();i++){
            glm::dvec3 relativePosition = shinyBalls[i]->getReference() - centreOfRoom;
            double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
            double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
            
            glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
            newPos[1] = shinyBalls[i]->getReference()[1];
            shinyBalls[i]->setReference(  newPos );
        }
     }
    }   
}

// }