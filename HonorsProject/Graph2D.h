/*
	Graph2D

	Stores 2D Graph Nodes.

	Velly Simeonov

*/

#pragma once
#ifndef GRAPH2D_H
#define GRAPH2D_H

#include "GraphNode2D.h"
#include "AVLTree.h"

class Graph2D {
private:
	AVLTree<GraphNode2D> nodes = AVLTree<GraphNode2D>(compareGraphNode2D);
	int _arrSize, _nodeCount = 0;
public:
	Graph2D() {	}
	~Graph2D() { }
	bool insert(GraphNode2D &input);
	bool remove(GraphNode2D &input);
	GraphNode2D* getNode(GraphNode2D &node);
	int nodeCount() const { return _nodeCount; }
	Queue<Queue<GraphNode2D*>*> breadthOrder();
};

#endif