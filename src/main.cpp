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

	::std::shared_ptr<Object> o1(new Object);

	::std::shared_ptr<Geometry> wall(new Sphere(10000));
	::std::shared_ptr<Material> whiteDiffuse(new DiffuseMaterial(Vector3(1,1,1)));

	o1->transform.setPosition(Vector3(10,10,30));
	o1->geometry=::std::shared_ptr<Geometry>(new Sphere(3));
	o1->material=whiteDiffuse;


	auto makeWall=[&scene,wall,whiteDiffuse](Vector3 pos){
		::std::shared_ptr<Object> w(new Object);
		w->geometry=wall;
		w->material=whiteDiffuse;
		w->transform.setPosition(pos);
		scene.addObject(w);
	};

	makeWall(Vector3(0,0,10200));
	// makeWall(Vector3(10100,0,100));
	// makeWall(Vector3(-10100,0,100));
	// makeWall(Vector3(0,10100,100));
	// makeWall(Vector3(0,-10100,100));

	scene.addObject(o1);

	::std::shared_ptr<Light> l(new PointLight(Vector3(10,10,10),Vector3(1,0.5,0)));

	scene.addLight(l);

	cam.render(bitmap,scene);

	::std::ofstream file("test.ppm",::std::ios::out|std::ios::binary);

	bitmap.exportAsPPM(file);

	return 0;
}