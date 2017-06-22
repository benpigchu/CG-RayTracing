#include <cmath>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "Vector3.h"
#include "Bitmap.h"
#include "AABB.h"
#include "Matrix4.h"
#include "Util.h"
#include "BezierCurve.h"
#include "Quaternion.h"
#include "Transform.h"
#include "Ray.h"
#include "Geometry.h"
#include "Sphere.h"
#include "Square.h"
#include "Material.h"
#include "DiffuseMaterial.h"
#include "MirrorMaterial.h"
#include "GlassMaterial.h"
#include "Light.h"
#include "PointLight.h"
#include "SquareLight.h"
#include "Object.h"
#include "Camera.h"
#include "RunTask.hpp"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshGeometry.h"

int main(int argc,char** argv){
	::std::cout<<"still working\n";

	Bitmap bitmap(200,200);

	Scene scene;

	Camera cam(100);

	::std::shared_ptr<Object> o1(new Object),o2(new Object),o3(new Object);

	::std::shared_ptr<Geometry> wall(new Sphere(10000));
	::std::shared_ptr<Material> whiteDiffuse(new DiffuseMaterial(Vector3(0.45,0.65,0.85)));
	::std::shared_ptr<Material> mirror(new MirrorMaterial(Vector3(0.8,0.8,0.8)));
	::std::shared_ptr<Material> glass(new GlassMaterial(1.2,Vector3(0.99,0.99,0.99)));

	// ::std::vector<::std::pair<double,double>> controls{{0,0},{1,0},{2,0},{2,1},{3,1}};
	// BezierCurve bc(controls);

	// ::std::ofstream file("bezier.obj",::std::ios::out);

	// Mesh::generateRotationFromBezier(bc,40,80).exportAsOBJ(file);

	::std::ifstream cubeFile("bezier.obj",::std::ios::in);
	Mesh m=Mesh::importFromOBJ(cubeFile);

	::std::shared_ptr<Geometry> mesh(new MeshGeometry(m,Vector3(10,-10,10)));
	o1->transform.setPosition(Vector3(10,40,120));
	o1->geometry=mesh;
	o1->material=whiteDiffuse;
	scene.addObject(o1);

	o2->transform.setPosition(Vector3(-40,40,100));
	o2->geometry=::std::shared_ptr<Geometry>(new Sphere(20));
	o2->material=glass;
	scene.addObject(o2);

	o3->transform.setPosition(Vector3(80,0,180));
	o3->transform.setRotation(Quaternion::fromAxisRotation(Vector3(0,1,0),-PI*3/4));
	o3->geometry=::std::shared_ptr<Geometry>(new Square(60));
	o3->material=mirror;
	scene.addObject(o3);

	auto makeWall=[&scene,wall](Vector3 pos,Vector3 color=Vector3(1,1,1)){
		::std::shared_ptr<Object> w(new Object);
		w->geometry=wall;
		w->material=::std::shared_ptr<Material>(new DiffuseMaterial(color));
		w->transform.setPosition(pos);
		scene.addObject(w);
	};

	makeWall(Vector3(0,0,10200));
	makeWall(Vector3(10100,0,100),Vector3(0,1,0));
	makeWall(Vector3(-10100,0,100),Vector3(1,0,0));
	makeWall(Vector3(0,10100,100),Vector3(1,0.5,0));
	makeWall(Vector3(0,-10100,100),Vector3(0,0,0));

	::std::shared_ptr<Light> l(new PointLight(Vector3(/*0.2,0.2,0.6*/1,1,1),Vector3(30,-30,100)));
	::std::shared_ptr<SquareLight> sql(new SquareLight(Vector3(1,1,1),10));
	sql->transform.setPosition(Vector3(0,-90,100));
	sql->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,0,0),-PI/2));

	scene.addLight(l);
	// scene.addLight(sql);

	// Renderer::rayTracing(bitmap,scene,cam);

	::std::ofstream file("test.ppm",::std::ios::out|std::ios::binary);

	bitmap.exportAsPPM(file);
	// auto x=glass->transformRay(Ray(Vector3(0,1,1)),Vector3(0,1,0),Vector3(0,0,0));

	::std::cout<<::std::endl;



	return 0;
}