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
#include "SortedLinkedListS.h"

class Graph2D {
private:
	SortedLinkedListS<GraphNode2D> *nodes;
	int _nodeCount = 0;
public:
	Graph2D() {
		nodes = new SortedLinkedListS<GraphNode2D>();
	}
	~Graph2D() {
		delete nodes;
	}
	int insert(const GraphNode2D& input);
	int remove(const GraphNode2D& input);
	GraphNode2D* getNode(const int& index);
	int nodeCount() { return _nodeCount; }
};

int Graph2D::insert(const GraphNode2D& input) {
	int x;
	if (x = nodes->insert(input))
		++_nodeCount;
	return x;
}

int Graph2D::remove(const GraphNode2D& input) {
	int x;
	if (x = nodes->remove(input))
		--_nodeCount;
	return x;
}

GraphNode2D* Graph2D::getNode(const int& index) {
	return nodes->get(index);
}

#endif