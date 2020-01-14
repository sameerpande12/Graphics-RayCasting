#include<iostream>
#include <limits>
#include<glm/glm.hpp>
using namespace std;
int main(){
    double t = std::numeric_limits<double>::infinity();
    cout<< (t==std::numeric_limits<double>::infinity())<<endl;

    glm::dmat3 v = glm::dmat3(1,2,3,4,5,6,7,8,9);

    
    for(int i =0;i<3;i++){
        for(int j=0;j<3;j++){
            std::cout<<v[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    glm::dvec3 x = v* glm::dvec3(1,1,1);
    for(int i=0;i<3;i++){
        std::cout<<x[i]<<" ";
    }
    std::cout<<"\n";

    glm::dvec3 myVec = glm::dvec3(t,t,t);
    for(int i = 0;i<3;i++)std::cout<<myVec[i]<<" ";
    std::cout<<"\n";
}