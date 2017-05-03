#ifndef RENDERER_H
#define RENDERER_H
#include "Bitmap.h"
#include "Camera.h"
#include "Scene.h"

namespace Renderer{
	void rayTracing(Bitmap& bitmap,const Scene& scene,const Camera& camera)noexcept;
}

#endif //RENDERER_H