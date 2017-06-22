#include <cstddef>
#include <functional>
#include "Vector3.h"
#include "KDTree.hpp"
#include "RunTask.hpp"
#include "HitPointHost.h"
#include "AABB.h"

AABB HitPointHost::getAABB(HitPoint hp)const noexcept{
	return AABB(hp.position,hp.position);
}

void HitPointHost::processNode(Node& node)const noexcept{
	if(node.datas.size()<=3){
		return;
	}else{
		Axis splitAxis=Axis::NONE;
		double maxDiff=0;
		if(maxDiff<=::std::abs(node.aabb.min.x-node.aabb.max.x)){
			maxDiff=::std::abs(node.aabb.min.x-node.aabb.max.x);
			splitAxis=Axis::X;
		}
		if(maxDiff<=::std::abs(node.aabb.min.y-node.aabb.max.y)){
			maxDiff=::std::abs(node.aabb.min.y-node.aabb.max.y);
			splitAxis=Axis::Y;
		}
		if(maxDiff<=::std::abs(node.aabb.min.z-node.aabb.max.z)){
			maxDiff=::std::abs(node.aabb.min.z-node.aabb.max.z);
			splitAxis=Axis::Z;
		}
		auto comparer=[splitAxis](HitPoint hp1,HitPoint hp2){
			switch(splitAxis){
			case Axis::X:
				return hp1.position.x<hp2.position.x;
				break;
			case Axis::Y:
				return hp1.position.y<hp2.position.y;
				break;
			case Axis::Z:
				return hp1.position.z<hp2.position.z;
				break;
			default:
				return true;
			}
		};
		//sort by pos
		::std::sort(node.datas.begin(),node.datas.end(),comparer);
		//split at middle
		::std::vector<HitPoint> l,r;
		::std::copy(node.datas.begin(),node.datas.begin()+node.datas.size()/2,::std::back_inserter(l));
		::std::copy(node.datas.begin()+node.datas.size()/2,node.datas.end(),::std::back_inserter(r));
		//make subnode
		node.left=this->makeNode(l);
		node.right=this->makeNode(r);
		//return
		node.datas.clear();
	}
}

void HitPointHost::forEach(::std::function<void(HitPoint&)> func)noexcept{
	runTaskLIFO<Node*>(this->root,[func](Node* node,auto addTask){
		if(node->left!=NULL||node->right!=NULL){
			addTask(node->left);
			addTask(node->right);
		}else{
			for(HitPoint& hp:node->datas){
				func(hp);
			}
		}
	});
}