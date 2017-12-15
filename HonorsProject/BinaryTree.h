/*
	Binary Tree template

	Fall 2017

	Velly Simeonov
*/

#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H
#define _template template<class T>

#include "Queue.h"

_template
class BinaryNode {
protected:
	void * _left;
	void * _right;
	T* _data;

public:
	BinaryNode(T& data) { _data = &data, _left = nullptr, _right = nullptr; }
	BinaryNode(T*& data) { _data = data, _left = nullptr, _right = nullptr; }
	BinaryNode(T*& data, BinaryNode * left, BinaryNode * right) {
		_data = data;
		_left = left;
		_right = right;
	}

	virtual ~BinaryNode() { }

	bool isLeaf() { return (_left == nullptr) && (_right == nullptr); }

	inline virtual BinaryNode<T>* getLeftPtr() { return (BinaryNode<T>*) _left; }
	inline virtual BinaryNode<T>* getRightPtr() { return (BinaryNode<T>*) _right; }
	inline virtual void setLeftPtr(BinaryNode<T>* tPtr) { _left = (void*)tPtr; }
	inline virtual void setRightPtr(BinaryNode<T>* tPtr) { _right = (void*)tPtr; }

	T* getData() { return _data; }
	void setData(T &item) { _data = &item; }
	void setData(T* &item) { _data = item; }
};

_template
class BinaryTree {
private:
protected:
	int _count;
	void* _rootNodePtr;

	virtual BinaryNode<T>* getRootPtr() const { return (BinaryNode<T>*) _rootNodePtr; }
	virtual void setRootPtr(BinaryNode<T>* newRoot) { _rootNodePtr = (void*)newRoot; }

public:
	virtual ~BinaryTree() { clear(); }

	BinaryTree & operator = (const BinaryTree & sourceTree);

	
	// common functions
	bool isEmpty() { return _count == 0; }
	int count() { return _count; }
	void clear() { _destroyTree(getRootPtr()); setRootPtr(nullptr); }


	// traversals
	int preOrder(Queue<T*> & queue, const bool &rightFirst = false) const;
	int inOrder(Queue<T*> & queue, const bool &rightFirst = false) const;
	int postOrder(Queue<T*> & queue, const bool &rightFirst = false) const;
	int breadthOrder(Queue<T*> & queue, const bool &rightFirst = false) const;


	// abstract functions
	virtual bool insert(T& item) = 0;
	virtual bool remove(T& item) = 0;
	virtual bool getEntry(T& item, T*& output) = 0;


	void getLeftMost(T* &item) const;
	void getRightMost(T* &item) const;


private:
	void _destroyTree(BinaryNode<T>* root);

	// traversals
	bool _preOrder(Queue<T*> &queue, BinaryNode<T> *nodePtr, const bool &rightFirst) const;
	bool _inOrder(Queue<T*> &queue, BinaryNode<T> *nodePtr, const bool &rightFirst) const;
	bool _postOrder(Queue<T*> &queue, BinaryNode<T> *nodePtr, const bool &rightFirst) const;

};

/************************\
	Public Functions
\************************/

_template
BinaryTree<T> & BinaryTree<T>::operator=(const BinaryTree<T> & sourceTree)
{
	if (this != &sourceTree) {
		this->clear();

		BinaryNode<T> *ptr;

		Queue<BinaryNode<T>*> nodes;
		nodes.enqueue(sourceTree->getRootPtr());

		_count = sourceTree._count;

		while (!nodes.isEmpty()) {
			nodes.dequeue(ptr);
			while (ptr) {
				nodes.enqueue(ptr->getLeftPtr());
				nodes.enqueue(ptr->getRightPtr());
				this->insert(ptr->getData());
				nodes.dequeue(ptr);
			}
		}
	}
	return *this;
}

_template
int BinaryTree<T>::preOrder(Queue<T*> &queue, const bool &rightFirst) const {
	if (!queue.isEmpty()) return 0;
	return _preOrder(queue, getRootPtr(), rightFirst);
}

_template
int BinaryTree<T>::inOrder(Queue<T*> &queue, const bool &rightFirst) const {
	if (!queue.isEmpty()) return 0;
	return _inOrder(queue, getRootPtr(), rightFirst);
}

_template
int BinaryTree<T>::postOrder(Queue<T*> &queue, const bool &rightFirst) const {
	if (!queue.isEmpty()) return 0;
	return _postOrder(queue, getRootPtr(), rightFirst);
}

_template
int BinaryTree<T>::breadthOrder(Queue<T*> &queue, const bool &rightFirst) const {
	Queue<BinaryNode<T>*> tmpQueue;
	tmpQueue.enqueue(getRootPtr());

	while (!tmpQueue.isEmpty()) {
		BinaryNode<T>* tmpNode, * first, * second;
		tmpQueue.dequeue(tmpNode);

		if (tmpNode) {
			if (rightFirst) {
				first = tmpNode->getRightPtr();
				second = tmpNode->getLeftPtr();
			}
			else {
				first = tmpNode->getLeftPtr();
				second = tmpNode->getRightPtr();
			}

			queue.enqueue(tmpNode->getData());
			tmpQueue.enqueue(first);
			tmpQueue.enqueue(second);
		}
	}
	return 0;
}

_template
void BinaryTree<T>::getLeftMost(T* &item) const {
	BinaryNode<T>* nodePtr = getRootPtr(), *last = nullptr;

	while (nodePtr != nullptr) {
		last = nodePtr;
		nodePtr = nodePtr->getLeftPtr();
	}
	if (last != nullptr) item = last->getData();
}

_template
void BinaryTree<T>::getRightMost(T* &item) const {
	BinaryNode<T>* nodePtr = getRootPtr(), last;

	while (nodePtr != nullPtr) {
		last = nodePtr;
		nodePtr = nodePtr->getRightPtr();
	}
}

/************************\
	Private Functions
\************************/

_template
void BinaryTree<T>::_destroyTree(BinaryNode<T>* targetDataNodePtr) {
	if (targetDataNodePtr == nullptr) return;

	BinaryNode<T> * curr = getRootPtr();

	// Locate Start

	while (curr != nullptr && curr->getData() != targetDataNodePtr->getData()) { // stop on nullptr or found
		if (targetDataNodePtr->getData() < curr->getData()) {
			curr = curr->getLeftPtr();
		}
		else {
			curr = curr->getRightPtr();
		}
	}

	if (curr == nullptr) return; // data does not exist in tree

	// End Locate

	// Start Deleting

	Queue<BinaryNode<T>*> nodeQueue;

	nodeQueue.enqueue(curr);

	while (!nodeQueue.isEmpty()) {
		nodeQueue.dequeue(curr);
		if (curr) {
			nodeQueue.enqueue(curr->getLeftPtr());
			nodeQueue.enqueue(curr->getRightPtr());
			delete curr;
			--_count;
		}
	}
	// End Deleting
}

_template
bool BinaryTree<T>::_preOrder(Queue<T*> &queue, BinaryNode<T> *nodePtr, const bool &rightFirst) const { // to do
	if (nodePtr != 0)
	{
		BinaryNode<T>* first = nodePtr->getLeftPtr(), *second = nodePtr->getRightPtr();

		if (rightFirst) {
			first = second;
			second = nodePtr->getLeftPtr();
		}

		T *item = nodePtr->getData();
		queue.enqueue(item);

		_preOrder(queue, first, rightFirst);
		
		_preOrder(queue, second, rightFirst);
		return true;
	}
	return false;
}

_template
bool BinaryTree<T>::_inOrder(Queue<T*> &queue, BinaryNode<T> *nodePtr, const bool &rightFirst) const { // to do
	if (nodePtr != 0)
	{
		BinaryNode<T>* first = nodePtr->getLeftPtr(), *second = nodePtr->getRightPtr();

		if (rightFirst) {
			first = second;
			second = nodePtr->getLeftPtr();
		}

		_inOrder(queue, first, rightFirst);

		T* item = nodePtr->getData();
		queue.enqueue(item);

		_inOrder(queue, second, rightFirst);
		return true;
	}
	return false;
}

_template
bool BinaryTree<T>::_postOrder(Queue<T*> &queue, BinaryNode<T> *nodePtr, const bool &rightFirst) const { // to do
	if (nodePtr != 0)
	{
		BinaryNode<T>* first = nodePtr->getLeftPtr(), *second = nodePtr->getRightPtr();

		if (rightFirst) {
			first = second;
			second = nodePtr->getLeftPtr();
		}

		_postOrder(queue, first, rightFirst);

		_postOrder(queue, second, rightFirst);

		T* item = nodePtr->getData();
		queue.enqueue(item);
		return true;
	}
	return false;
}


#endif // !BINARYTREE_H
