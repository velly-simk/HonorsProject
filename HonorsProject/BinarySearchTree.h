/*
	BST template

	Fall 2017

	Velly Simeonov
*/

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
	/* copy nodes */
	BinaryNode<T>* _copyTree(BinaryNode<T>* root);

	/* insert node into tree */
	BinaryNode<T>* _insert(BinaryNode<T> * root, BinaryNode<T> * newNode);

	/* locate and delete node from tree */
	BinaryNode<T>* _removeNode(BinaryNode<T> * root, T &target, bool &success);

	/* delete node called by remove*/
	BinaryNode<T>* _deleteNode(BinaryNode<T> * targetNode);

	/* remove left most node of tree from root */
	BinaryNode<T>* _removeLeftMostNode(BinaryNode<T> * root, T * &successor);

	/* locate node with target as data*/
	BinaryNode<T>* _findNode(BinaryNode<T> * root, T &target);

public:
	/* normal constructor */
	BinarySearchTree(int compareFunction(T &lhs, T &rhs), bool duplicates = false) {
		this->setRootPtr(nullptr);
		this->_count = 0;
		comp = compareFunction;
		this->_allowDuplicates = duplicates;
	}

	/* copy constructor */
	BinarySearchTree(const BinarySearchTree &tree) {
		this->setRootPtr(this->_copyTree(tree.getRootPtr()));
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
	this->setRootPtr(_insert(this->getRootPtr(), node));
	return tmp != _count;
}

_template
bool BinarySearchTree<T>::remove(T& item) {
	bool success = false;

	this->setRootPtr(_removeNode(this->getRootPtr(), item, success));

	return success;
}

_template
bool BinarySearchTree<T>::getEntry(T& item, T*& output) {
	BinaryNode<T> * node = nullptr;
	node = _findNode(this->getRootPtr(), item);

	if (node == nullptr) return false;

	output = node->getData();

	return true;
}


/************************\
	Private Functions
\************************/

_template
BinaryNode<T>* BinarySearchTree<T>::_copyTree(BinaryNode<T>* startNodePtr) {
	BinaryNode<T> * node = nullptr;
	if (startNodePtr != nullptr) {
		T* data = startNodePtr->getData();
		node = new BinaryNode<T>(data,
			startNodePtr->getLeftPtr(),
			startNodePtr->getRightPtr());
	}
	return node;
}

_template
BinaryNode<T>* BinarySearchTree<T>::_insert(BinaryNode<T> * root, BinaryNode<T> * newNode) {
	if (root == nullptr) {
		++this->_count;
		return root = newNode;
	}
	else {
		int x = comp(*newNode->getData(), *root->getData());

		if (x > 0) {
			root->setRightPtr(_insert(root->getRightPtr(), newNode));
			return root;
		}
		else if (x < 0) {
			root->setLeftPtr(_insert(root->getLeftPtr(), newNode));
			return root;
		}
		else if (x == 0 && this->_allowDuplicates) {
			root->setRightPtr(_insert(root->getRightPtr(), newNode));
			return root;
		}
		else return root;
	}
}

_template
BinaryNode<T>* BinarySearchTree<T>::_removeNode(BinaryNode<T> * root, T &target, bool &success) {
	if (root == nullptr) {
		success = false;
		return nullptr;
	}
	int x = comp(target, *root->getData());

	if (x > 0) {
		root->setRightPtr(_removeNode(root->getRightPtr(), target, success));

	}
	else if (x < 0) {
		root->setLeftPtr(_removeNode(root->getLeftPtr(), target, success));
	}
	else {
		root = _deleteNode(root);
		success = true;
		--_count;
	}
	return root;
}

_template
BinaryNode<T>* BinarySearchTree<T>::_deleteNode(BinaryNode<T> * targetNode) {
	BinaryNode<T>* tmpPtr;
	if (targetNode->isLeaf()) {
		delete targetNode;
		targetNode = nullptr;
		return targetNode;
	}
	else if (targetNode->getLeftPtr() == nullptr) {
		tmpPtr = targetNode->getRightPtr();
		delete targetNode;
		targetNode = 0;
		return tmpPtr;
	}
	else if (targetNode->getRightPtr() == nullptr) {
		tmpPtr = targetNode->getLeftPtr();
		delete targetNode;
		targetNode = 0;
		return tmpPtr;
	}
	else {
		T* val;
		targetNode->setRightPtr(_removeLeftMostNode(targetNode->getRightPtr(), val));
		targetNode->setData(val);
		return targetNode;
	}
}

_template
BinaryNode<T>* BinarySearchTree<T>::_removeLeftMostNode(BinaryNode<T> * root, T * &successor) {
	if (root->getLeftPtr() == nullptr)
	{
		successor = root->getData();
		return _deleteNode(root);
	}
	else
	{
		root->setLeftPtr(_removeLeftMostNode(root->getLeftPtr(), successor));
		return root;
	}
}

_template
BinaryNode<T>* BinarySearchTree<T>::_findNode(BinaryNode<T>* root, T &target) {
	if (root == nullptr) {
		return nullptr;
	}
	else {
		int x = comp(target, *root->getData());
		if ( x > 0 ) {
			return _findNode(root->getRightPtr(), target);
		}
		else if (x < 0) {
			return _findNode(root->getLeftPtr(), target);
		}
		else {
			return root;
		}
	}
}

#endif // !BINARYSEARCHTREE_H
