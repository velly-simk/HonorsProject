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

class Graph2D {
private:
	GraphNode2D** nodes;
	int _arrSize, _nodeCount = 0;
public:
	Graph2D() {
		nodes = new GraphNode2D*[8]();
	}
	~Graph2D() {
		delete[] nodes;
	}
	int insert(const GraphNode2D* & input);
	int remove(const GraphNode2D* & input);
	GraphNode2D* getNode(const int& index);
	int nodeCount() { return _nodeCount; }
};

#endif