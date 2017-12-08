#pragma once
#ifndef _BINARY_NODE_H
#define _BINARY_NODE_H
#define _template template<class T>

_template
class BinaryNode {
public:
	BinaryNode<T>* _left;
	BinaryNode<T>* _right;
	T* _data;
	BinaryNode(T& data) { _data = &data, _left = nullptr, _right = nullptr; }
	BinaryNode(T*& data) { _data = data, _left = nullptr, _right = nullptr; }
	BinaryNode(T*& data, BinaryNode * left, BinaryNode * right) {
		_data = data;
		_left = left;
		_right = right;
	}
	bool isLeaf() { return (_left == nullptr) && (_right == nullptr); }
};



#endif // !_BINARY_NODE_H
