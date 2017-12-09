#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#define _template template<class T>

#include "BinaryTree.h"

_template
class AVLNode : public BinaryNode<T> {
private:
	short _balanceFactor = 0;
public:
	AVLNode(T& data) : BinaryNode<T>(data) { }
	AVLNode(T*& data) : BinaryNode<T>(data) { }
	AVLNode(T*& data, AVLNode * left, AVLNode * right) : BinaryNode<T>(data, left, right) { }

	virtual ~AVLNode() { }

	AVLNode<T>* getLeftPtr() { return (AVLNode<T>*) _left; }
	AVLNode<T>* getRightPtr() { return (AVLNode<T>*) _right; }
	void setLeftPtr(AVLNode<T>* tPtr) { _left = (void*)tPtr; }
	void setRightPtr(AVLNode<T>* tPtr) { _right = (void*)tPtr; }
};

_template
class AVLTree : public BinaryTree<T> {
protected:
	/* comp function returns [-1,1] ex: comp(int a, int b) returns 1 if a>b, -1 if b>a, and 0 if a == b */
	int(*comp)(T & lhs, T & rhs);

	bool _allowDuplicates;

	AVLNode<T>* getRootPtr() { return (AVLNode<T>*) _rootNodePtr; }
	void setRootPtr(AVLNode<T>* newRoot) { _rootNodePtr = (void*)newRoot; }

private:
	/* insert node into tree */
	AVLNode<T>* _insert(AVLNode<T> * root, AVLNode<T> * newNode);

	/* locate and delete node from tree */
	AVLNode<T>* _removeNode(AVLNode<T> * root, T &target, bool &success);

	/* delete node called by remove*/
	AVLNode<T>* _deleteNode(AVLNode<T> * targetNode);

	/* remove left most node of tree from root */
	AVLNode<T>* _removeLeftMostNode(AVLNode<T> * root, T * &successor);

	/* locate node with target as data*/
	AVLNode<T>* _findNode(AVLNode<T> * root, T &target);

public:
	/* normal constructor */
	AVLTree(int compareFunction(T &lhs, T &rhs), bool duplicates = false) {
		this->setRootPtr(nullptr);
		this->_count = 0;
		comp = compareFunction;
		this->_allowDuplicates = duplicates;
	}

	/* copy constructor */
	AVLTree(const AVLTree &tree) {
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
bool AVLTree<T>::insert(T& item) {
	AVLNode<T> * node = new AVLNode<T>(item);
	int tmp = _count;
	this->setRootPtr(_insert(this->getRootPtr(), node));
	return tmp != _count;
}

_template
bool AVLTree<T>::remove(T& item) {
	bool success = false;

	this->setRootPtr(_removeNode(this->getRootPtr(), item, success));

	return success;
}

_template
bool AVLTree<T>::getEntry(T& item, T*& output) {
	AVLNode<T> * node = nullptr;
	node = _findNode(this->getRootPtr(), item);

	if (node == nullptr) return false;

	output = node->getData();

	return true;
}


/************************\
Private Functions
\************************/

_template
AVLNode<T>* AVLTree<T>::_insert(AVLNode<T> * root, AVLNode<T> * newNode) {
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
AVLNode<T>* AVLTree<T>::_removeNode(AVLNode<T> * root, T &target, bool &success) {
	if (root == nullptr) {
		success = false;
		return nullptr;
	}
	int x = comp(target, *root->getData());

	if (x > 0) {
		_removeNode(root->getRightPtr(), target, success);
	}
	else if (x < 0) {
		_removeNode(root->getLeftPtr(), target, success);
	}
	else {
		root = _deleteNode(root);
		success = true;
		--_count;
	}
	return root;
}

_template
AVLNode<T>* AVLTree<T>::_deleteNode(AVLNode<T> * targetNode) {
	AVLNode<T>* tmpPtr;
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
/* remove left most node of tree from root */
AVLNode<T>* AVLTree<T>::_removeLeftMostNode(AVLNode<T> * root, T * &successor) {
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
AVLNode<T>* AVLTree<T>::_findNode(AVLNode<T>* root, T &target) {
	if (root == nullptr) {
		return nullptr;
	}
	else {
		int x = comp(target, *root->getData());
		if (x > 0) {
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


#endif // !AVLTREE_H
