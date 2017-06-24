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
#include "WeightTexturedMaterial.h"

int main(int argc,char** argv){
	::std::cout<<"still working\n";

	Bitmap bitmap(600,600);

	Scene scene;

	Camera cam(600);
	cam.transform.setPosition(Vector3(0,0,-100));

	::std::shared_ptr<Object> o1(new Object),o2(new Object),o3(new Object),o4(new Object);

	::std::shared_ptr<Geometry> wall(new Sphere(10000));
	::std::shared_ptr<Material> blueDiffuse(new DiffuseMaterial(Vector3(0.2,0.4,0.6)));
	::std::shared_ptr<Material> whiteDiffuse(new DiffuseMaterial(Vector3(1,1,1)));
	::std::shared_ptr<Material> mirror(new MirrorMaterial(Vector3(0.8,0.8,0.8)));
	::std::shared_ptr<Material> glass(new GlassMaterial(1.5,Vector3(0.99,0.99,0.99)));

	// ::std::vector<::std::pair<double,double>> controls{{0,0},{6,0},{0,4},{1,8}};
	// BezierCurve bc(controls);

	// ::std::ofstream modulefile("bezier.obj",::std::ios::out);

	// Mesh::generateRotationFromBezier(bc,320,160).exportAsOBJ(modulefile);

	::std::ifstream bezierFile("bezier.obj",::std::ios::in);
	Mesh m=Mesh::importFromOBJ(bezierFile);

	::std::shared_ptr<Geometry> mesh(new MeshGeometry(m,Vector3(15,15,15)));
	o1->transform.setPosition(Vector3(-50,100,140));
	o1->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,0,0),PI));
	o1->geometry=mesh;
	o1->material=blueDiffuse;
	scene.addObject(o1);

	o2->transform.setPosition(Vector3(40,70,125));
	o2->geometry=::std::shared_ptr<Geometry>(new Sphere(30));
	o2->material=glass;
	scene.addObject(o2);

	o3->transform.setPosition(Vector3(80,0,180));
	o3->transform.setRotation(Quaternion::fromAxisRotation(Vector3(0,1,0),PI*1/4));
	o3->geometry=::std::shared_ptr<Geometry>(new Square(60));
	o3->material=mirror;
	scene.addObject(o3);

	::std::ifstream textureFile("out.ppm",::std::ios::in|std::ios::binary);
	Bitmap texture=Bitmap::importFromPPM(textureFile);

	o4->transform.setPosition(Vector3(0,0,195));
	o4->geometry=::std::shared_ptr<Geometry>(new Square(40));
	o4->material=::std::shared_ptr<Material>(new WeightTexturedMaterial(texture,whiteDiffuse));
	scene.addObject(o4);

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
	::std::shared_ptr<SquareLight> sql(new SquareLight(Vector3(1,1,1),40));
	sql->transform.setPosition(Vector3(0,-90,100));
	sql->transform.setRotation(Quaternion::fromAxisRotation(Vector3(1,0,0),PI/2));

	// scene.addLight(l);
	scene.addLight(sql);

	// Renderer::rayTracing(bitmap,scene,cam);
	Renderer::PhotonMappingEngine ppm(bitmap,scene,cam);
	ppm.setupHitPoint();
	int passNum=20000;
	for(int i=0;i<passNum;i++){
		ppm.processPhoton(10000);
		::std::cout<<"iter "<<i<<"/"<<passNum<<::std::endl;
	}
	ppm.writeBitmap();

	::std::ofstream file("test.ppm",::std::ios::out|std::ios::binary);

	bitmap.exportAsPPM(file);

	::std::cout<<::std::endl;

	return 0;
}