#include <iostream>

#include "Graph2D.h"

using namespace std;

int insertNodes(Graph2D& graph);


int main(int argc, char *argv[])
{
	Graph2D graph;

	insertNodes(graph);

	for (int i = 0; i < graph.nodeCount(); ++i) {
		cout << graph.getNode(i+1)->X() << " " << graph.getNode(i+1)->Y() << endl;
	}

	getchar();
    return 0;
}

int insertNodes(Graph2D& graph) {
	GraphNode2D x = GraphNode2D(1, 1),
		y = GraphNode2D(1, 2),
		z = GraphNode2D(2, 1),
		a = GraphNode2D(3, 1);

	graph.insert(x);
	graph.insert(y);
	graph.insert(z);
	graph.insert(a);

	return 0;
}