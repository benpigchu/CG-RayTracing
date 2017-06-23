#ifndef RENDERER_H
#define RENDERER_H
#include <cstddef>
#include <ctime>
#include <vector>
#include <tuple>
#include <random>
#include "Vector3.h"
#include "Bitmap.h"
#include "Camera.h"
#include "Scene.h"
#include "HitPointHost.h"

namespace Renderer{
	void rayTracing(Bitmap& bitmap,const Scene& scene,const Camera& camera)noexcept;
	class PhotonMappingEngine{
		static const double ALPHA;
		::std::default_random_engine ranGen;
		Bitmap& bitmap;
		const Scene& scene;
		const Camera& camera;
		HitPointHost hpHost;
		::std::vector<::std::tuple<ptrdiff_t,ptrdiff_t,Vector3>> litHitRecord;
		double initRadius;
		public:
		PhotonMappingEngine(Bitmap& bitmap,const Scene& scene,const Camera& camera,double initRadius=3)noexcept:bitmap(bitmap),scene(scene),camera(camera),initRadius(initRadius),ranGen(::std::time(NULL)){}
		void setupHitPoint()noexcept;
		void processPhoton(size_t pass)noexcept;
		void writeBitmap()noexcept;
	};
}

#endif //RENDERER_H