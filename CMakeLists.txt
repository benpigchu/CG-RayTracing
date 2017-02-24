cmake_minimum_required(VERSION 3.6)
project(CG-RayTracing)

include_directories(src)
include_directories(src/headers)

add_executable(rt
	src/Scene.cpp
	src/Sphere.cpp
	src/main.cpp
	)