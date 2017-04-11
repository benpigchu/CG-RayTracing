#include <iostream>
#include "Vector3.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Sphere.h"

int main(int argc,char** argv){
	::std::cout<<"still working\n";
	Matrix4 m(2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0);
	::std::cout<<m*m;
	// ::std::cout<<Sphere(1,Vector3(1,0,0)).testIntersect(Ray(Vector3(1,0,0),Vector3(1,0.5,0)));
	return 0;
}