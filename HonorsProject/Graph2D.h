/*
	Graph2D

	Stores 2D Graph Nodes and 2D Graph Links.

	Inserted Nodes are copied and independent from
	scope at insertion.

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
	int insert(const GraphNode2D* & input);
	int remove(const GraphNode2D* & input);
	GraphNode2D* getNode(const int& index);
	int nodeCount() { return _nodeCount; }
};

#endif