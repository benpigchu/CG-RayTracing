cmake_minimum_required(VERSION 3.6)
project(CG-RayTracing)

include_directories(src)
include_directories(src/headers)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(rt
	src/AABB.cpp
	src/BezierCurve.cpp
	src/Bitmap.cpp
	src/DiffuseMaterial.cpp
	src/GlassMaterial.cpp
	src/HitPointHost.cpp
	src/Mesh.cpp
	src/MeshGeometry.cpp
	src/MeshIntersectOptimiser.cpp
	src/MirrorMaterial.cpp
	src/Object.cpp
	src/PointLight.cpp
	src/Renderer.cpp
	src/Scene.cpp
	src/Sphere.cpp
	src/Square.cpp
	src/SquareLight.cpp
	src/Triangle.cpp
	src/WeightTexturedMaterial.cpp
	src/main.cpp
	)