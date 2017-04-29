#include <cstddef>
#include "Camera.h"
#include "Bitmap.h"
#include "Scene.h"

void Camera::render(Bitmap& bitmap,const Scene& scene)noexcept{
	size_t height=bitmap.getHeight();
	size_t width=bitmap.getWidth();
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			float x=i+0.5-width/2.0;
			float y=j+0.5-height/2.0;
			auto result=scene.testIntersect(this->makeRay(x,y));
			if(result.second.isIntersect){
				bitmap.at(i,j)=Vector3(10,10,10);
			}else{
				bitmap.at(i,j)=Vector3(0,0,0);
			}
		}
	}
}