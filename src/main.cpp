#include <cmath>
#include <memory>
#include <iostream>
#include <fstream>
#include "Vector3.h"
#include "Bitmap.h"
#include "Matrix4.h"
#include "Util.h"
#include "Quaternion.h"
#include "Transform.h"
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"
#include "Camera.h"

int main(int argc,char** argv){
	::std::cout<<"still working\n";

	Scene scene;

	// Camera cam(1000,Vector3(10,10,10),Quaternion::fromAxisRotation(Vector3(1,1,1),2*PI/3));

	::std::shared_ptr<Object> o1(new Object),o2(new Object);

	o1->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,1,0),0));
	o1->transform.setPosition(Vector3(0,0,3));
	o1->geometry=std::shared_ptr<Geometry>(new Sphere(1));

	o2->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,1,0),0));
	o2->transform.setPosition(Vector3(0,0,5));
	o2->geometry=std::shared_ptr<Geometry>(new Sphere(1));

	scene.addObject(o1);
	scene.addObject(o2);

	::std::cout<<scene.testIntersect(Ray(Vector3(0,0,-1),Vector3(0,0,7))).second;
	return 0;
}