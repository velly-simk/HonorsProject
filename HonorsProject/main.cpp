#include <iostream>

#include "Graph2D.h"
#include "BinarySearchTree2.h"

using namespace std;

int insertNodes(Graph2D& graph);


int main(int argc, char *argv[])
{
	BinarySearchTree<GraphNode2D> bst = BinarySearchTree<GraphNode2D>(compareGraphNode2D);
	GraphNode2D* x = new GraphNode2D(1, 1, 'a'),
		*y = new GraphNode2D(1, 2, 'a'),
		*z = new GraphNode2D(2, 1, 'a'),
		*a = new GraphNode2D(3, 1, 'a');
	
	bst.insert(*x);
	bst.insert(*y);
	bst.insert(*z);
	bst.insert(*a);

	Queue<GraphNode2D*> aaa;
	bst.inOrder(aaa, true);

	while (!aaa.isEmpty()) {
		GraphNode2D * a;
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << endl;
	}


	getchar();
    return 0;
}

int insertNodes(Graph2D& graph) {

	return 0;
}