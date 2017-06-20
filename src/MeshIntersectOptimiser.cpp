#include <algorithm>
#include <cmath>
#include <iterator>
#include "Util.h"
#include "KDTree.hpp"
#include "RunTask.hpp"
#include "Geometry.h"
#include "AABB.h"
#include "Triangle.h"
#include "MeshIntersectOptimiser.h"

#include <iostream>

AABB MeshIntersectOptimiser::getAABB(Triangle d)const noexcept{
	double xmin=::std::min(d.point[0].x,::std::min(d.point[1].x,d.point[2].x));
	double ymin=::std::min(d.point[0].y,::std::min(d.point[1].y,d.point[2].y));
	double zmin=::std::min(d.point[0].z,::std::min(d.point[1].z,d.point[2].z));
	double xmax=::std::max(d.point[0].x,::std::max(d.point[1].x,d.point[2].x));
	double ymax=::std::max(d.point[0].y,::std::max(d.point[1].y,d.point[2].y));
	double zmax=::std::max(d.point[0].z,::std::max(d.point[1].z,d.point[2].z));
	return AABB(Vector3(xmin,ymin,zmin),Vector3(xmax,ymax,zmax));
}

// this construct process only looks good when there are no large triangles
void MeshIntersectOptimiser::processNode(Node& node)const noexcept{
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
		auto comparer=[splitAxis](Triangle tri1,Triangle tri2){
			Vector3 center1=(tri1.point[0]+tri1.point[1]+tri1.point[2])/3;
			Vector3 center2=(tri2.point[0]+tri2.point[1]+tri2.point[2])/3;
			switch(splitAxis){
			case Axis::X:
				return center1.x<center2.x;
				break;
			case Axis::Y:
				return center1.y<center2.y;
				break;
			case Axis::Z:
				return center1.z<center2.z;
				break;
			default:
				return true;
			}
		};
		//sort by pos
		::std::sort(node.datas.begin(),node.datas.end(),comparer);
		//split at middle
		::std::vector<Triangle> l,r;
		::std::copy(node.datas.begin(),node.datas.begin()+node.datas.size()/2,::std::back_inserter(l));
		::std::copy(node.datas.begin()+node.datas.size()/2,node.datas.end(),::std::back_inserter(r));
		//make subnode
		node.left=this->makeNode(l);
		node.right=this->makeNode(r);
		//return
		node.datas.clear();
	}
}

IntersectInfo MeshIntersectOptimiser::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	ii.isIntersect=false;
	struct IntersectTestTask{
		Node* node;
		AABBIntersectInfo aabbii;
	};
	IntersectTestTask init{this->root,this->root->aabb.testIntersect(r)};
	if(init.aabbii.isIntersect==false){
		return ii;
	}
	runTaskLIFO<IntersectTestTask>(init,[&ii,r](IntersectTestTask task,auto addTask){
		if(ii.isIntersect){
			if(ii.distance<task.aabbii.near){
				return;
			}
		}
		if(task.node->left!=NULL||task.node->right!=NULL){
			AABBIntersectInfo laabbii=task.node->left->aabb.testIntersect(r);
			AABBIntersectInfo raabbii=task.node->right->aabb.testIntersect(r);
			if(laabbii.isIntersect){
				if(raabbii.isIntersect){
					if(laabbii.near<raabbii.near){
						addTask({task.node->right,raabbii});
						addTask({task.node->left,laabbii});
					}else{
						addTask({task.node->left,laabbii});
						addTask({task.node->right,raabbii});
					}
				}else{
					addTask({task.node->left,laabbii});
				}
			}else{
				if(raabbii.isIntersect){
					addTask({task.node->right,raabbii});
				}
			}
			return;
		}else{
			for(Triangle tri:task.node->datas){
				IntersectInfo newii=tri.testIntersect(r);
				if(newii.isIntersect){
					if(ii.isIntersect){
						if(ii.distance>=newii.distance){
							ii=newii;
						}
					}else{
						ii=newii;
					}
				}
			}
		}
	});
	::std::cout<<ii<<::std::endl;
	return ii;
}