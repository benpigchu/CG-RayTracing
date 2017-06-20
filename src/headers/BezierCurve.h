#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H
#include <vector>
#include <utility>

struct BezierCurve{
	private:
	::std::vector<::std::pair<double,double>> points;
	public:
	BezierCurve(::std::vector<::std::pair<double,double>> points)noexcept:points(points){}
	::std::pair<double,double> getPoint(double t)const noexcept;
};

#endif //BEZIERCURVE_H