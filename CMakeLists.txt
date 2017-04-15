cmake_minimum_required(VERSION 3.6)
project(CG-RayTracing)

include_directories(src)
include_directories(src/headers)

add_executable(rt
	src/Bitmap.cpp
	src/Scene.cpp
	src/Sphere.cpp
	src/Object.cpp
	src/main.cpp
	)