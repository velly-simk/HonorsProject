#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#define _template template<class T>

#include "BinaryTree2.h"

_template
class BinarySearchTree : public BinaryTree<T> {
protected:
	/* comp function returns [-1,1] ex: comp(int a, int b) returns 1 if a>b, -1 if b>a, and 0 if a == b */
	int (*comp)(T & lhs, T & rhs);

	bool _allowDuplicates;

private:
	/* insert node into tree */
	BinaryNode<T>* _insert(BinaryNode<T>* & root, BinaryNode<T>* & newNode);

	/* locate and delete node from tree */
	BinaryNode<T>* _removeNode(BinaryNode<T> * root, const T & target, bool & success) { return nullptr; }

	/* delete node called by remove*/
	BinaryNode<T>* _deleteNode(BinaryNode<T> * targetNode) { return nullptr; }

	/* remove left most node of tree from root */
	BinaryNode<T>* _removeLeftMostNode(BinaryNode<T> & root, T & successor) { return nullptr; }

	/* locate node with target as data*/
	BinaryNode<T>* _findNode(BinaryNode<T> & root, const T & target) { return nullptr; }

public:
	/* normal constructor */
	BinarySearchTree(int compareFunction(T &lhs, T &rhs), bool duplicates = false) {
		this->_rootNodePtr = nullptr;
		this->_count = 0;
		comp = compareFunction;
		this->_allowDuplicates = duplicates;
	}

	/* copy constructor */
	BinarySearchTree(const BinarySearchTree &tree) {
		this->_rootNodePtr = this->_copyTree(tree._rootNodePtr);
		this->count = tree._count;
		this->comp = tree.comp;
		this->_allowDuplicates = tree._allowDuplicates;
	}

	/* insert item to tree */
	bool insert(T& item);

	/* remove item from tree*/
	bool remove(const T& item);

	/* get item*/
	bool getEntry(const T& item, T*& output) const;
};

/************************\
	Public Functions
\************************/

_template
bool BinarySearchTree<T>::insert(T& item) {
	BinaryNode<T> * node = new BinaryNode<T>(item);
	int tmp = _count;
	_insert(this->_rootNodePtr, node);
	return tmp != _count;
}

_template
bool BinarySearchTree<T>::remove(const T& item) {
	bool success = false;

	this->_rootNodePtr = _removeNode(this->_rootNodePtr, item, success);

	return success;
}
_template
bool BinarySearchTree<T>::getEntry(const T& item, T*& output) const {
	BinaryNode<T> * node = nullptr;
//	node = _findNode(_rootNodePtr, item);

	if (node == nullptr) return false;

	output = node->_data;

	return true;
}


/************************\
	Private Functions
\************************/

_template
BinaryNode<T>* BinarySearchTree<T>::_insert(BinaryNode<T>* & root, BinaryNode<T>* & newNode) {
	if (root == nullptr) {
		++this->_count;
		return root = newNode;
	}
	else {
		int x = comp(*newNode->_data, *root->_data);
		if (x > 0)
			return _insert(root->_right, newNode);
		else if (x < 0)
			return _insert(root->_left, newNode);
		else if (x == 0 && this->_allowDuplicates)
			return _insert(root->_right, newNode);
		else return nullptr;
	}
}

#endif // !BINARYSEARCHTREE_H
