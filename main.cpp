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
#include "scene.h"
#include "GLFW/glfw3.h"
#include "GL/glew.h"
#include <cmath>

#define cout std::cout
#define endl std::endl

void keyCallback(GLFWwindow* window,int key, int scancode,int action,int mods);


Camera* camera;
int toggleValue = 0;
std::vector<Sphere*> shinyBalls;
std::vector<Wall*> walls;
std::vector<Sphere*> snowSpheres;
std::vector<Object*> objects;
std::vector<PointSource*> pointSources;
std::vector<Cylinder*> tubeLights;
std::vector<PointSource*> lightSources;

double R = 5;
double circleRadius = 1.5*R;
glm::dvec3 centreOfRoom = glm::dvec3(2*R,2*R,-2*R);

#define QUIT(m,v)      { fprintf(stderr, "%s:%s\n", m, v); exit(1); }
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void initializeGlfwGLEW(GLFWwindow ** window,int WIDTH,int HEIGHT){
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

    *window = glfwCreateWindow(WIDTH, HEIGHT, "main", NULL, NULL);
    if (!window) {
        glfwTerminate();
        QUIT("gWindow_GLFW", "Could not create Window");
    }

    glfwMakeContextCurrent(*window);

    if ( GLEW_OK != glewInit() ) {
        glfwTerminate();
        QUIT("gWindow_GLFW","glewInit failed");
    }

    glfwSwapInterval(1);
    
    glEnable(GL_TEXTURE_2D);

}

int main(int argc,char*argv[]){

    int WIDTH = std::stoi(argv[1]);//requested WIDTH
    int HEIGHT = std::stoi(argv[2]);//requested HEIGHT
    

    GLFWwindow * window;
    initializeGlfwGLEW(& window, WIDTH, HEIGHT);

    int width,height;
    glfwGetFramebufferSize(window, &width, &height);//save the alloted width and height
    glfwSetKeyCallback(window,keyCallback);
    OpenGLdraw opengl;
    opengl.init(width, height);
   

    
    GLubyte image[height*width*3];
    

    glm::dvec3 cameraPosition = glm::dvec3(2*R,2*R,3*R);
    Axes xyz = Axes();
    xyz.setAxes(glm::dvec3(1,0,0),glm::dvec3(0,1,0),glm::dvec3(0,0,1));
    camera = new Camera();
    camera->location = cameraPosition;
    camera->axes = xyz;
    camera->width = width;
    camera->height = height;
    camera->fov = M_PI_2;
    createScene(lightSources,pointSources,tubeLights,shinyBalls,snowSpheres,walls,objects,R,width,height);
    
    int aliasingValue = 4;
    std::vector<double>deltaX;
    std::vector<double> deltaY;

    for(int i= 0;i<aliasingValue;i++){
        deltaX.push_back(drand48()*0.5);
        deltaY.push_back(drand48()*0.5);
    }
    while(!glfwWindowShouldClose(window)){   
        glfwPollEvents();
        double start = omp_get_wtime();
        #pragma omp parallel for
        for(int iter = 0;iter<height*width;iter++){
                int i,j;
                i = iter/width;
                j = iter%width;
                glm::dvec3 colorObtained=glm::dvec3(0,0,0);
                for(int aliasNumber = 0;aliasNumber<aliasingValue;aliasNumber++){
                    
                
                    glm::dvec3 rayDir = glm::normalize(camera->pixelToWorld( (double)j+deltaX[aliasNumber],(double)i+deltaY[aliasNumber]) - camera->location);
                
                    Ray ray = Ray(camera->location,rayDir,1);
                    colorObtained += rayTrace(ray,objects,lightSources,1,4,glm::dvec3(0,0,0));
                }
                colorObtained = colorObtained * (1/ (double)aliasingValue);
                
                for(int i = 0;i<3;i++)if(colorObtained[i]>1)colorObtained[i]=0.9999;
                image[iter*3]=(GLubyte) (colorObtained[0]*255);
                image[iter*3+1]=(GLubyte) (colorObtained[1]*255);
                image[iter*3+2]=(GLubyte) (colorObtained[2]*255);
                
        
        }
        double end = omp_get_wtime();
        cout<<end-start<<endl;
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        opengl.draw(image,width,height,0,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }    
    
    
}

void keyCallback(GLFWwindow* window,int key, int scancode,int action,int mods){
    if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
    else if(key == GLFW_KEY_T && action == GLFW_PRESS){
        toggleValue = (toggleValue+1)%3;
        cout<<"Key t is pressed. t ="<<toggleValue<<endl;

    }
    else if(toggleValue == 0){//rotate entire scene
        if( (key==GLFW_KEY_UP || key==GLFW_KEY_DOWN) && action==GLFW_PRESS ){
            double angle = M_PI_4/3;//15 degrees
            if(key==GLFW_KEY_UP)angle = -angle;
            
            camera->axes = rotateAxes(camera->axes,angle,0);
            cout<<"New camera axes are-> ";
            printAxes(camera->axes);
            cout<<'\n';

            // for(int i = 0;i<(int)shinyBalls.size();i++){//rotate about x axis
            //     glm::dvec3 relativePosition = shinyBalls[i]->getReference() - centreOfRoom;
            //     double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
            //     double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
            //     glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
            //     newPos[0] = shinyBalls[i]->getReference()[0];
            //     shinyBalls[i]->setReference(  newPos );
            // }


            // for(int i = 0;i<(int)walls.size();i++){
            //     std::vector<glm::dvec3>cornerPoints = walls[i]->getPoints();

            //     for(int j = 0;j<(int)cornerPoints.size();j++){//rotate about x axis
            //         glm::dvec3 relativePosition = cornerPoints[j] - centreOfRoom;
            //         double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
            //         double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
            //         glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
            //         newPos[0] = cornerPoints[j][0];
            //         cornerPoints[j]=newPos;
            //     }
            //     walls[i]->updatePoints(cornerPoints);

            // }


            // for(int i = 0;i<(int)snowSpheres.size();i++){//rotate about x axis
            //     glm::dvec3 relativePosition = snowSpheres[i]->getReference() - centreOfRoom;
            //     double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
            //     double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
            //     glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
            //     newPos[0] = snowSpheres[i]->getReference()[0];
            //     snowSpheres[i]->setReference(  newPos );
            // }

            // for(int i = 0;i<(int)pointSources.size();i++){
            //     //rotate about x axis
            //     glm::dvec3 relativePosition = pointSources[i]->position - centreOfRoom;
            //     double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
            //     double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
            //     glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
            //     newPos[0] = pointSources[i]->position[0];
            //     pointSources[i]->position = newPos;
            // }

            // for(int i =0 ;i<(int)tubeLights.size();i++){

            //     glm::dvec3 relativePosition = tubeLights[i]->getReference() - centreOfRoom;
            //     double newY = cos(angle)* relativePosition[1] - sin(angle)*relativePosition[2];
            //     double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[1];
                
            //     glm::dvec3 newPos = centreOfRoom + glm::dvec3(0,newY,newZ);
            //     newPos[0] = tubeLights[i]->getReference()[0];
                

            //     Axes newAxes = rotateAxes(tubeLights[i]->getAxes(),angle,0);
            //     tubeLights[i]->updatePosition(newPos,newAxes);
                
            // }




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

            for(int i = 0;i<(int)pointSources.size();i++){//rotate only point sources (not included in tubelight)
                glm::dvec3 relativePosition = pointSources[i]->position - centreOfRoom;
                double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                newPos[1] = pointSources[i]->position[1];
                pointSources[i]->position = newPos;
            }

            for(int i = 0;i<(int)snowSpheres.size();i++){//rotate about x axis
                glm::dvec3 relativePosition = snowSpheres[i]->getReference() - centreOfRoom;
                double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                newPos[1] = snowSpheres[i]->getReference()[1];
                snowSpheres[i]->setReference(  newPos );
            }



            for(int i = 0;i<(int)tubeLights.size();i++){//rotate only point sources (not included in tubelight)
                glm::dvec3 relativePosition = tubeLights[i]->getReference() - centreOfRoom;
                double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                
                glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                newPos[1] = tubeLights[i]->getReference()[1];
                
                Axes newAxes = rotateAxes(tubeLights[i]->getAxes(),angle,1);//rotate about y -axis
                tubeLights[i]->updatePosition(newPos,newAxes);
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
    else if(toggleValue==2){
        if( (key==GLFW_KEY_LEFT || key==GLFW_KEY_RIGHT) && action==GLFW_PRESS){
            double angle = M_PI_4/3;
            if(key==GLFW_KEY_RIGHT)angle = -angle;
            for(int i = 0;i<(int)tubeLights.size();i++){//rotate only point sources (not included in tubelight)
                    glm::dvec3 relativePosition = tubeLights[i]->getReference() - centreOfRoom;
                    double newX = cos(angle)* relativePosition[0] - sin(angle)*relativePosition[2];
                    double newZ = cos(angle)* relativePosition[2] + sin(angle)*relativePosition[0];
                    
                    glm::dvec3 newPos = centreOfRoom + glm::dvec3(newX,0,newZ);
                    newPos[1] = tubeLights[i]->getReference()[1];
                    
                    Axes newAxes = rotateAxes(tubeLights[i]->getAxes(),angle,1);//rotate about y -axis
                    tubeLights[i]->updatePosition(newPos,newAxes);
            }
        }
    }   
}

// }