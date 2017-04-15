#include <cmath>
#include <memory>
#include <iostream>
#include "Vector3.h"
#include "Matrix4.h"
#include "Util.h"
#include "Quaternion.h"
#include "Transform.h"
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"

int main(int argc,char** argv){
	::std::cout<<"still working\n";
	::std::cout<<Sphere(1).testIntersect(Ray(Vector3(0.5,0.5,0),Vector3(0.5,0.7,0)));
	Object o;
	o.transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,1,0),0));
	o.transform.setPosition(Vector3(0,0,1));
	o.geometry=std::shared_ptr<Geometry>(new Sphere(1));
	::std::cout<<o.testIntersect(Ray(Vector3(0.5,0.5,0),Vector3(0.5,0.7,1)));
	return 0;
}