#include<iostream>
#include <limits>
#include<glm/glm.hpp>
using namespace std;
int main(){
    double t = std::numeric_limits<double>::infinity();
    cout<< (t==std::numeric_limits<double>::infinity())<<endl;

    glm::dvec3 v = glm::dvec3(1,1,1);
    v = v*t;
    cout<<v[0]<<endl;
    cout<<isinf(v[1]);
}