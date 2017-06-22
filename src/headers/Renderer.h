#ifndef RENDERER_H
#define RENDERER_H
#include <cstddef>
#include <vector>
#include <tuple>
#include "Vector3.h"
#include "Bitmap.h"
#include "Camera.h"
#include "Scene.h"
#include "HitPointHost.h"

namespace Renderer{
	void rayTracing(Bitmap& bitmap,const Scene& scene,const Camera& camera)noexcept;
	class PhotonMappingEngine{
		Bitmap& bitmap;
		const Scene& scene;
		const Camera& camera;
		HitPointHost hpHost;
		::std::vector<::std::tuple<ptrdiff_t,ptrdiff_t,Vector3>> litHitRecord;
		PhotonMappingEngine(Bitmap& bitmap,const Scene& scene,const Camera& camera)noexcept:bitmap(bitmap),scene(scene),camera(camera){}
		public:
		void setupHitPoint()noexcept;
		void processPhoton(size_t pass)noexcept;
		void writeBitmap()noexcept;
	};
}

#endif //RENDERER_H