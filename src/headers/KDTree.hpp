#ifndef KDTREE_H
#define KDTREE_H
#include <cstddef>
#include <memory>
#include <vector>
#include "AABB.h"

// base class to create kd-tree struct
// when reference the vector of data
// and the data should not modified when the tree is created
template<typename Data>
class KDTree{
	protected:
	::std::vector<Data>& data;
	/*todo--define virtual function*/
	struct Node{
		::std::unique_ptr<Node> l,r;
		AABB aabb;
		ptrdiff_t begin,end;
	}
	::std::unique_ptr<Node> root;
	KDTree(::std::vector<Data>& data)noexcept:data(data){
		/*todo*/
	}
};

#endif //KDTREE_H