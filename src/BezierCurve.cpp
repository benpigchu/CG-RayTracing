#include <cstddef>
#include <vector>
#include <utility>
#include "BezierCurve.h"

::std::pair<double,double> BezierCurve::getPoint(double t)const noexcept{
	::std::vector<::std::pair<double,double>> tmp(this->points);
	if(tmp.size()==0){
		return ::std::make_pair(0.0,0.0);
	}
	while(tmp.size()>1){
		for(ptrdiff_t i=0;i<tmp.size()-1;i++){
			tmp[i].first=tmp[i+1].first*t+tmp[i].first*(1-t);
			tmp[i].second=tmp[i+1].second*t+tmp[i].second*(1-t);
		}
		tmp.pop_back();
	}
	return tmp[0];
};