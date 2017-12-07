#include <iostream>

#include "Graph2D.h"
#include "BinarySearchTree2.h"

using namespace std;

int insertNodes(Graph2D& graph);


int main(int argc, char *argv[])
{
	BinarySearchTree<GraphNode2D> bst;
	GraphNode2D* x = new GraphNode2D(1, 1, 'a'),
		*y = new GraphNode2D(1, 2, 'a'),
		*z = new GraphNode2D(2, 1, 'a'),
		*a = new GraphNode2D(3, 1, 'a');

	GraphNode2D** arr = new GraphNode2D*();
	x->Links(arr);


	for (int i = 0; i < 4; ++i) {
		if (arr[i] == nullptr) {
			cout << "empty" << endl;
			continue;
		}
		cout << arr[i]->X() << " " << arr[i]->Y() << endl;
	}


	getchar();
    return 0;
}

int insertNodes(Graph2D& graph) {

	return 0;
}