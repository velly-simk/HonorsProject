#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H
#define _template template<class T>

#include "Queue.h"

_template
class BinaryTree {
protected:
	struct BinaryNode {
		BinaryNode* _left;
		BinaryNode* _right;
		T _data;
		BinaryNode(const T& data) { _data = data, _left = nullptr, _right = nullptr; }
		BinaryNode(const T& data, BinaryNode * left, BinaryNode * right) {
			_data = data;
			_left = left;
			_right = right;
		}
		bool isLeaf() { return (_left == nullptr) && (_right == nullptr); }
	};

	BinaryNode* _rootNodePtr;
	int _count;

public:
	BinaryTree() { _rootNodePtr = nullptr; _count = 0; }
	BinaryTree(const BinaryTree<T> & tree) { this = tree; }
	virtual ~BinaryTree() { clear(); }

	BinaryTree & operator = (const BinaryTree & sourceTree); // to do

	
	// common functions
	bool isEmpty() { return _count == 0; }
	int count() { return _count; }
	void clear() { _destroyTree(_rootNodePtr); _rootNodePtr = nullptr; }


	// traversals
	int preOrder(Queue<T*> & queue, const bool rightFirst = false) const;
	int inOrder(Queue<T*> & queue, const bool rightFirst = false) const;
	int postOrder(Queue<T*> & queue, const bool rightFirst = false) const;
	int breadthOrder(Queue<T*> & queue) const;


	// abstract functions
	virtual bool insert(const T& item) = 0;
	virtual bool remove(const T& item) = 0;
	virtual bool getEntry(const T& item, T& output) const = 0;


	void getLeftMost(T &item) const;
	void getRightMost(T &item) const;


private:
	//BinaryNode* _copyTree(const BinaryNode* &root); cant return protected struct
	void _destroyTree(BinaryNode* &root);

	// traversals
	int _preOrder(Queue<T*> &queue, const BinaryNode* &nodePtr, const bool &rightFirst) const;
	int _inOrder(Queue<T*> &queue, const BinaryNode* &nodePtr, const bool &rightFirst) const;
	int _postOrder(Queue<T*> &queue, const BinaryNode* &nodePtr, const bool &rightFirst) const;

};

/************************\
	Public Functions
\************************/

_template
BinaryTree<T> & BinaryTree<T>::operator=(const BinaryTree<T> & sourceTree)
{
	if (this != &sourceTree) {
		this->clear();

		BinaryNode *ptr;

		Queue<BinaryNode*> nodes;
		nodes.enqueue(sourceTree._rootNodePtr);

		_count = sourceTree._count;

		while (!nodes.isEmpty()) {
			nodes.dequeue(ptr);
			while (ptr) {
				nodes.enqueue(ptr->_left);
				nodes.enqueue(ptr->_right);
				this->insert(ptr->_data);
				nodes.dequeue(ptr);
			}
		}
	}
	return *this;
}

_template
int BinaryTree<T>::preOrder(Queue<T*> &queue, const bool rightFirst) const {
	if (!queue.isEmpty()) return 0;
	return _preOrder(*queue, _rootNodePtr, rightFirst);
}

_template
int BinaryTree<T>::inOrder(Queue<T*> &queue, const bool rightFirst) const {
	if (!queue.isEmpty()) return 0;
	return _inOrder(*queue, _rootNodePtr, rightFirst);
}

_template
int BinaryTree<T>::postOrder(Queue<T*> &queue, const bool rightFirst) const {
	if (!queue.isEmpty()) return 0;
	return _postOrder(*queue, _rootNodePtr, rightFirst);
}

_template

int BinaryTree<T>::breadthOrder(Queue<T*> &queue) const {
	Queue<BinaryNode*> tmpQueue;
	tmpQueue.enqueue(_rootNodePtr);

	while (!tmpQueue.isEmpty()) {
		BinaryNode* tmpNode;
		tmpQueue.dequeue(tmpNode);

		if (tmpNode) {
			queue.enqueue(&tmpNode->_data);
			tmpQueue.enqueue(tmpNode->_left);
			tmpQueue.enqueue(tmpNode->_right);
		}
	}

}

_template
void BinaryTree<T>::getLeftMost(T &item) const {
	BinaryNode* nodePtr = _rootNodePtr, last;

	while (nodePtr != nullPtr) {
		last = nodePtr;
		nodePtr = nodePtr->_left;
	}
}

_template
void BinaryTree<T>::getRightMost(T &item) const {
	BinaryNode* nodePtr = _rootNodePtr, last;

	while (nodePtr != nullPtr) {
		last = nodePtr;
		nodePtr = nodePtr->_right;
	}
}

/************************\
	Private Functions
\************************/
/* cant return protected struct
_template
BinaryNode* BinaryTree<T>::_copyTree(const BinaryNode* &startNodePtr) {
	BinaryNode * node = nullptr;
	if (startNodePtr != nullptr) {
		node = new BinaryNode(startNodePtr->_data,
			_copyTree(startNodePtr->_left),
			_copyTree(startNodePtr->_right));
	}
}
*/
_template
void BinaryTree<T>::_destroyTree(BinaryNode* &targetDataNodePtr) {
	if (targetDataNodePtr == nullptr) return;

	BinaryNode * curr = _rootNodePtr;

	// Locate Start

	while (curr != nullptr && curr->_data != targetDataNodePtr->_data) { // stop on nullptr or found
		if (targetDataNodePtr->_data < curr->_data) {
			curr = curr->_left;
		}
		else {
			curr = curr->_right;
		}
	}

	if (curr == nullptr) return; // data does not exist in tree

	// End Locate

	// Start Deleting

	Queue<BinaryNode*> nodeQueue;

	nodeQueue.enqueue(curr);

	while (!nodeQueue.isEmpty()) {
		nodeQueue.dequeue(curr);
		if (curr) {
			nodeQueue.enqueue(curr->_left);
			nodeQueue.enqueue(curr->_right);
			delete curr;
			--_count;
		}
	}
	// End Deleting
}

_template
int BinaryTree<T>::_preOrder(Queue<T*> &queue, const BinaryNode* &nodePtr, const bool &rightFirst) const { // to do
	if (nodePtr != 0)
	{
		BinaryNode* first, second;
		if (rightFirst) {
			first = nodePtr->_right;
			second = nodePtr->_left;
		}
		else {
			first = nodePtr->_left;
			second = nodePtr->_right;
		}
		T* item = &nodePtr->getItem();
		queue.enqueue(item);

		_preOrder(queue, first, rightFirst);
		
		_preOrder(queue, second, rightFirst);
		return 1;
	}
	return 0;
}

_template
int BinaryTree<T>::_inOrder(Queue<T*> &queue, const BinaryNode* &nodePtr, const bool &rightFirst) const { // to do
	if (nodePtr != 0)
	{
		BinaryNode* first, second;
		if (rightFirst) {
			first = nodePtr->_right;
			second = nodePtr->_left;
		}
		else {
			first = nodePtr->_left;
			second = nodePtr->_right;
		}
		_inOrder(queue, first, rightFirst);

		T* item = &nodePtr->getItem();
		queue.enqueue(item);

		_inOrder(queue, second, rightFirst);
		return 1;
	}
	return 0;
}

_template
int BinaryTree<T>::_postOrder(Queue<T*> &queue, const BinaryNode* &nodePtr, const bool &rightFirst) const { // to do
	if (nodePtr != 0)
	{
		BinaryNode* first, second;
		if (rightFirst) {
			first = nodePtr->_right;
			second = nodePtr->_left;
		}
		else {
			first = nodePtr->_left;
			second = nodePtr->_right;
		}
		_postOrder(queue, first, rightFirst);

		_postOrder(queue, second, rightFirst);

		T* item = &nodePtr->getItem();
		queue.enqueue(item);
		return 1;
	}
	return 0;
}
#endif // !BINARYTREE_H
