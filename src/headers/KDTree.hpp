#ifndef KDTREE_H
#define KDTREE_H
#include <cstddef>
#include <limits>
#include <algorithm>
#include <vector>
#include "RunTask.hpp"
#include "AABB.h"
#include "Util.h"

#include <iostream>

// base class to create kd-tree struct
template<typename Data,typename NodeInfo=Nothing>
class KDTree{
	protected:
	// get AABB of data
	virtual AABB getAABB(Data d)const noexcept=0;
	struct Node{
		Node *left,*right;
		AABB aabb;
		NodeInfo info;
		::std::vector<Data> datas;
	};
	// generate subNode
	virtual void processNode(Node& node)const noexcept=0;
	Node* root;
	inline Node* makeNode(::std::vector<Data> datas)const noexcept{
		double minx=::std::numeric_limits<double>::infinity(),miny=::std::numeric_limits<double>::infinity(),minz=::std::numeric_limits<double>::infinity();
		double maxx=-::std::numeric_limits<double>::infinity(),maxy=-::std::numeric_limits<double>::infinity(),maxz=-::std::numeric_limits<double>::infinity();
		for(Data data:datas){
			AABB aabb=getAABB(data);
			minx=::std::min(minx,::std::min(aabb.min.x,aabb.max.x));
			maxx=::std::max(maxx,::std::max(aabb.min.x,aabb.max.x));
			miny=::std::min(miny,::std::min(aabb.min.y,aabb.max.y));
			maxy=::std::max(maxy,::std::max(aabb.min.y,aabb.max.y));
			minz=::std::min(minz,::std::min(aabb.min.z,aabb.max.z));
			maxz=::std::max(maxz,::std::max(aabb.min.z,aabb.max.z));
		}
		return new Node{NULL,NULL,AABB(Vector3(minx,miny,minz),Vector3(maxx,maxy,maxz)),NodeInfo(),datas};
	}
	inline void removeNode(Node* n)const noexcept{
		runTaskLIFO<Node*>(n,[](Node* node,auto addTask){
			if(node!=NULL){
				addTask(node->left);
				addTask(node->right);
				delete node;
			}
		});
	}
	~KDTree()noexcept{
		removeNode(this->root);
	}
	public:
	void init(::std::vector<Data> datas)noexcept{
		removeNode(this->root);
		this->root=makeNode(datas);
		runTaskLIFO<Node*>(this->root,[this](Node* node,auto addTask){
			if(node!=NULL){
				this->processNode(*node);
				addTask(node->left);
				addTask(node->right);
			}
		});
	}
};

#endif //KDTREE_H