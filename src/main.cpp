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
#include "Geometry.h"
#include "Sphere.h"
#include "Material.h"
#include "DiffuseMaterial.h"
#include "Light.h"
#include "PointLight.h"
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
	o1->geometry=::std::shared_ptr<Geometry>(new Sphere(3));
	o1->material=::std::shared_ptr<Material>(new DiffuseMaterial(Vector3(0.2,0.2,0.2)));

	o2->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,1,0),0));
	o2->transform.setPosition(Vector3(0,0,150));
	o2->geometry=::std::shared_ptr<Geometry>(new Sphere(100));
	o2->material=::std::shared_ptr<Material>(new DiffuseMaterial(Vector3(0.2,0.2,0.2)));

	scene.addObject(o1);
	scene.addObject(o2);

	::std::shared_ptr<Light> l(new PointLight(Vector3(10,10,10),Vector3(1,0.5,0)));

	scene.addLight(l);

	cam.render(bitmap,scene);

	::std::ofstream file("test.ppm",::std::ios::out|std::ios::binary);

	bitmap.exportAsPPM(file);

	return 0;
}