OS := $(shell uname)
CFLAGS = -lglut -lglfw -Wall -lGL -ldl -lGLEW -fopenmp -O3

exe: main.o 
	g++ main.o scene.o OpenGLdraw.o Camera.o Box.o Wall.o Cylinder.o Sphere.o Object.o helper.o Axes.o Ray.o PointSource.o  $(CFLAGS) -o exe

main.o: main.cpp scene.o OpenGLdraw.o Camera.o Box.o Wall.o Cylinder.o Sphere.o Object.o helper.o Axes.o Ray.o PointSource.o 
	g++  $(CFLAGS) -c main.cpp 


scene.o: scene.cpp scene.h  Camera.o Box.o Wall.o Cylinder.o Sphere.o Object.o helper.o Axes.o Ray.o PointSource.o 
	g++  $(CFLAGS) -c scene.cpp 

OpenGLdraw.o: OpenGLdraw.cpp OpenGLdraw.h 
	g++ $(CFLAGS) -c OpenGLdraw.cpp

Camera.o: Camera.cpp Camera.h Ray.o helper.o Axes.o 
	g++ $(CFLAGS) -c Camera.cpp

Box.o: Box.cpp Box.h Object.o helper.o Axes.o Ray.o PointSource.o
	g++ $(CFLAGS) -c Box.cpp 

Wall.o: Wall.cpp Wall.h Object.o helper.o Axes.o Ray.o PointSource.o
	g++ $(CFLAGS) -c Wall.cpp

Cylinder.o: Cylinder.cpp Cylinder.h Object.o helper.o Axes.o Ray.o PointSource.o
	g++ $(CFLAGS) -c Cylinder.cpp

Sphere.o: Sphere.cpp Sphere.h Object.o helper.o Axes.o Ray.o PointSource.o
	g++ $(CFLAGS) -c Sphere.cpp

Object.o: Object.cpp Object.h helper.cpp helper.h Axes.o Ray.o PointSource.o
	g++ $(CFLAGS) -c Object.cpp

helper.o: helper.cpp helper.h Axes.o Object.cpp Object.h Ray.o PointSource.o
	g++ $(CFLAGS) -c helper.cpp

Axes.o: Axes.cpp Axes.h
	g++ $(CFLAGS) -c Axes.cpp

Ray.o: Ray.cpp Ray.h
	g++ $(CFLAGS) -c Ray.cpp

PointSource.o: PointSource.cpp PointSource.h
	g++ $(CFLAGS) -c PointSource.cpp

clean:
	rm *.o exe