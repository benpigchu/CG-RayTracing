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
		double maxRadius;
		double photonNum=0;
		public:
		PhotonMappingEngine(Bitmap& bitmap,const Scene& scene,const Camera& camera,double maxRadius=5)noexcept:bitmap(bitmap),scene(scene),camera(camera),maxRadius(maxRadius),ranGen(::std::time(NULL)){}
		void setupHitPoint()noexcept;
		void processPhoton(size_t pass)noexcept;
		void writeBitmap()noexcept;
	};
}

#endif //RENDERER_H