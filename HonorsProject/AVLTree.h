#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#define _template template<class T>

#include "BinarySearchTree.h"

_template
class AVLTree : public BinarySearchTree<T> {
protected:
	struct AVLNode : protected BinaryTree<T>::BinaryNode<T> {
		int _depth, 
			_depthFactor;
	};


};




#endif // !AVLTREE_H
