#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#define _template template<class T>

#include "BinaryTree.h"

_template
class BinarySearchTree : public BinaryTree<T> {
protected:
	/* comp function returns [-1,1] ex: comp(int a, int b) returns 1 if a>b, -1 if b>a, and 0 if a == b */
	int (*comp)(T & lhs, T & rhs);

	bool _allowDuplicates;

private:
	/* insert node into tree */
	BinaryNode<T>* _insert(BinaryNode<T> * &root, BinaryNode<T> * &newNode);

	/* locate and delete node from tree */
	BinaryNode<T>* _removeNode(BinaryNode<T> * &root, T &target, bool &success);

	/* delete node called by remove*/
	BinaryNode<T>* _deleteNode(BinaryNode<T> * &targetNode);

	/* remove left most node of tree from root */
	BinaryNode<T>* _removeLeftMostNode(BinaryNode<T> * &root, T * &successor);

	/* locate node with target as data*/
	BinaryNode<T>* _findNode(BinaryNode<T> * &root, T &target);

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
	bool remove(T& item);

	/* get item*/
	bool getEntry(T& item, T*& output);
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
bool BinarySearchTree<T>::remove(T& item) {
	bool success = false;

	this->_rootNodePtr = _removeNode(this->_rootNodePtr, item, success);

	return success;
}

_template
bool BinarySearchTree<T>::getEntry(T& item, T*& output) {
	BinaryNode<T> * node = nullptr;
	node = _findNode(_rootNodePtr, item);

	if (node == nullptr) return false;

	output = node->_data;

	return true;
}


/************************\
	Private Functions
\************************/

_template
BinaryNode<T>* BinarySearchTree<T>::_insert(BinaryNode<T> * &root, BinaryNode<T> * &newNode) {
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

_template
BinaryNode<T>* BinarySearchTree<T>::_removeNode(BinaryNode<T> * &root, T &target, bool &success) {
	if (root == nullptr) {
		success = false;
		return nullptr;
	}
	int x = comp(target, *root->_data);
	if (x > 0) {
		_removeNode(root->_right, target, success);
	}
	else if (x < 0) {
		_removeNode(root->_left, target, success);
	}
	else {
		root = _deleteNode(root);
		success = true;
	}
	return root;
}

_template
BinaryNode<T>* BinarySearchTree<T>::_deleteNode(BinaryNode<T> * &targetNode) {
	if (targetNode->isLeaf()) {
		delete targetNode;
		targetNode = nullptr;
		return targetNode;
	}
	else if (targetNode->_left == nullptr) {
		BinaryNode<T>* tmp = targetNode->_right;
		delete targetNode;
		targetNode = 0;
		return tmp;
	}
	else if (targetNode->_right == nullptr) {
		BinaryNode<T> * tmp = targetNode->_left;
		delete targetNode;
		targetNode = 0;
		return tmp;
	}
	else {
		T* val;
		targetNode->_right = _removeLeftMostNode( targetNode->_right, val);
		targetNode->_data = val;
		return targetNode;
	}
}

_template
/* remove left most node of tree from root */
BinaryNode<T>* BinarySearchTree<T>::_removeLeftMostNode(BinaryNode<T> * &root, T * &successor) {
	if (root->_left == nullptr)
	{
		successor = root->_data;
		return _deleteNode(root);
	}
	else
	{
		root->_left = _removeLeftMostNode(root->_left, successor);
		return root;
	}
}

_template
BinaryNode<T>* BinarySearchTree<T>::_findNode(BinaryNode<T>* &root, T &target) {
	if (root == nullptr) {
		return nullptr;
	}
	else {
		int x = comp(target, *root->_data);
		if ( x > 0 ) {
			return _findNode(root->_right, target);
		}
		else if (x < 0) {
			return _findNode(root->_left, target);
		}
		else {
			return root;
		}
	}
}

#endif // !BINARYSEARCHTREE_H
