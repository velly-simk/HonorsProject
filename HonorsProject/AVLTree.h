/*
	AVL Tree template

	does not allow duplicates

	Fall 2017

	Velly Simeonov
*/

#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#define _template template<class T>

#include "BinaryTree.h"

#include <iostream>

_template
class AVLNode : public BinaryNode<T> {
public:
	AVLNode(T& data) : BinaryNode<T>(data) { }
	AVLNode(T*& data) : BinaryNode<T>(data) { }
	AVLNode(T*& data, AVLNode * left, AVLNode * right) : BinaryNode<T>(data, left, right) { }

	virtual ~AVLNode() { }

	AVLNode<T>* getLeftPtr() { return (AVLNode<T>*) _left; }
	AVLNode<T>* getRightPtr() { return (AVLNode<T>*) _right; }
	void setLeftPtr(AVLNode<T>* tPtr) { _left = (void*)tPtr; }
	void setRightPtr(AVLNode<T>* tPtr) { _right = (void*)tPtr; }

	int _depth = 1;
};

_template
class AVLTree : public BinaryTree<T> {
protected:
	/* comp function returns [-1,1] ex: comp(int a, int b) returns 1 if a>b, -1 if b>a, and 0 if a == b */
	int(*comp)(T & lhs, T & rhs);

//	bool _allowDuplicates = false;

	AVLNode<T>* getRootPtr() { return (AVLNode<T>*) _rootNodePtr; }
	void setRootPtr(AVLNode<T>* newRoot) { _rootNodePtr = (void*)newRoot; }

private:
	/* copy nodes */
	AVLNode<T>* _copyTree(AVLNode<T>* root);

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

	/* resolves node depth */
	void _depthResolution(AVLNode<T> * &root);

	/* rotates tree from node left */
	AVLNode<T>* _leftRotation(AVLNode<T> * node);

	/* rotates tree from node right */
	AVLNode<T>* _rightRotation(AVLNode<T> * node);

	/* logic for AVL balance rotations */
	void _balance(AVLNode<T> * & node);

	/* calculates balance factor of node */
	int _balFactor(AVLNode<T> * node) const;

public:
	/* normal constructor */
	AVLTree(int compareFunction(T &lhs, T &rhs), bool duplicates = false) {
		this->setRootPtr(nullptr);
		this->_count = 0;
		comp = compareFunction;
//		this->_allowDuplicates = duplicates;
	}
	/* copy constructor */
	AVLTree(AVLTree &tree) {
		this->setRootPtr(this->_copyTree(tree.getRootPtr()));
		this->_count = tree._count;
		this->comp = tree.comp;
//		this->_allowDuplicates = tree._allowDuplicates;
	}

	/* insert item to tree */
	bool insert(T& item);

	/* remove item from tree*/
	bool remove(T& item);

	/* get item*/
	bool getEntry(T& item, T*& output);
	
	/* prints out depths of nodes in breadth order*/
	void printBreadthOrderDepths();
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

_template
void AVLTree<T>::printBreadthOrderDepths() {
	Queue<AVLNode<T>*> nodeQueue;
	AVLNode<T> * tmp;

	nodeQueue.enqueue((AVLNode<T>*)_rootNodePtr);

	while (!nodeQueue.isEmpty()) {
		nodeQueue.dequeue(tmp);
		if (tmp != nullptr) {
			nodeQueue.enqueue(tmp->getLeftPtr());
			nodeQueue.enqueue(tmp->getRightPtr());
			std::cout << "Depth :" << tmp->_depth << std::endl;
		}
	}


}


/************************\
	Private Functions
\************************/

_template
AVLNode<T>* AVLTree<T>::_copyTree(AVLNode<T>* startNodePtr) {
	AVLNode<T> * node = nullptr;
	if (startNodePtr != nullptr) {
		T* data = startNodePtr->getData();
		node = new AVLNode<T>(data,
			startNodePtr->getLeftPtr(),
			startNodePtr->getRightPtr());
	}
	return node;
}

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
			_depthResolution(root);
			_balance(root);
			return root;
		}
		else if (x < 0) {
			root->setLeftPtr(_insert(root->getLeftPtr(), newNode));
			_depthResolution(root);
			_balance(root);
			return root;
		}
		
/*		else if (x == 0 && this->_allowDuplicates) {
			root->setRightPtr(_insert(root->getRightPtr(), newNode));
			_depthResolution(root);
			_balance(root);
			return root;
		}
*/		
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
		root->setRightPtr(_removeNode(root->getRightPtr(), target, success));
			_depthResolution(root);
			_balance(root);
	}
	else if (x < 0) {
		root->setLeftPtr(_removeNode(root->getLeftPtr(), target, success));
			_depthResolution(root);
			_balance(root);
	}
	else {
		root = _deleteNode(root);
		if (root != nullptr) {
			_depthResolution(root);
			_balance(root);
		}
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
AVLNode<T>* AVLTree<T>::_removeLeftMostNode(AVLNode<T> * root, T * &successor) {
	if (root->getLeftPtr() == nullptr)
	{
		successor = root->getData();
		return _deleteNode(root);
	}
	else
	{
		root->setLeftPtr(_removeLeftMostNode(root->getLeftPtr(), successor));
		_depthResolution(root);
		_balance(root);
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

_template
void AVLTree<T>::_depthResolution(AVLNode<T> * &root) {
	int x = 0, y = 0;
	if (root->getLeftPtr() != nullptr)
		x = root->getLeftPtr()->_depth;
	if (root->getRightPtr() != nullptr)
		y = root->getRightPtr()->_depth;

	root->_depth = (x > y ? x : y) + 1;
}

_template
AVLNode<T> * AVLTree<T>::_leftRotation(AVLNode<T> * unbalancedNode) {
	AVLNode<T> * rightNode = unbalancedNode->getRightPtr();
	unbalancedNode->setRightPtr(rightNode->getLeftPtr());
	rightNode->setLeftPtr(unbalancedNode);

	return rightNode;
}

_template
AVLNode<T> * AVLTree<T>::_rightRotation(AVLNode<T> * unbalancedNode) {
	AVLNode<T> * leftNode = unbalancedNode->getLeftPtr();
	unbalancedNode->setLeftPtr(leftNode->getRightPtr());
	leftNode->setRightPtr(unbalancedNode);

	return leftNode;
}

_template
void AVLTree<T>::_balance(AVLNode<T> * & node) {
	AVLNode<T> * tmp;

	if (_balFactor(node) > 1) {
		if (_balFactor(node->getLeftPtr()) < 0) {
			node->setLeftPtr(_leftRotation(node->getLeftPtr()));
			tmp = node->getLeftPtr()->getLeftPtr();
			 _depthResolution(tmp); // left rotation gurantees no nullptr
			 tmp = node->getLeftPtr();
			_depthResolution(tmp);
		}
		node = _rightRotation(node);
		tmp = node->getRightPtr();
		_depthResolution(tmp);
		tmp = node;
		_depthResolution(tmp);
	}
	else if (_balFactor(node) < -1) {
		if (_balFactor(node->getRightPtr()) > 0) {
			node->setRightPtr(_rightRotation(node->getRightPtr()));
			tmp = node->getRightPtr()->getRightPtr();
			_depthResolution(tmp); // right rotation guarantees no nullptr
			tmp = node->getRightPtr();
			_depthResolution(tmp);
		}
		node = _leftRotation(node);
		tmp = node->getLeftPtr();
		_depthResolution(tmp);
		tmp = node;
		_depthResolution(tmp);
	}


}

_template
int AVLTree<T>::_balFactor(AVLNode<T> * node) const {
	int x = 0, y = 0;
	if (node->getLeftPtr() != nullptr)
		x = node->getLeftPtr()->_depth;
	if (node->getRightPtr() != nullptr)
		y = node->getRightPtr()->_depth;
	return  x - y;
}

#endif // !AVLTREE_H
