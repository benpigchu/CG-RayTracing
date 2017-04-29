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
#include "RunTask.hpp"

int main(int argc,char** argv){
	::std::cout<<"still working\n";

	Bitmap bitmap(100,100);

	Scene scene;

	Camera cam(100);

	::std::shared_ptr<Object> o1(new Object),o2(new Object);

	o1->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,1,0),0));
	o1->transform.setPosition(Vector3(10,10,30));
	o1->geometry=std::shared_ptr<Geometry>(new Sphere(3));

	o2->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,1,0),0));
	o2->transform.setPosition(Vector3(0,0,50));
	o2->geometry=std::shared_ptr<Geometry>(new Sphere(5));

	scene.addObject(o1);
	scene.addObject(o2);

	cam.render(bitmap,scene);

	::std::ofstream file("test.ppm",::std::ios::out|std::ios::binary);

	bitmap.exportAsPPM(file);

	return 0;
}