#include <iostream>

#include "Graph2D.h"
#include "BinarySearchTree.h"

using namespace std;

void printBST(BinarySearchTree<GraphNode2D> &bst);


int main(int argc, char *argv[])
{
	BinarySearchTree<GraphNode2D> bst = BinarySearchTree<GraphNode2D>(compareGraphNode2D, true);
	GraphNode2D* x = new GraphNode2D(1, 1, 'a'),
		*y = new GraphNode2D(1, 2, 'a'),
		*z = new GraphNode2D(2, 1, 'a'),
		*a = new GraphNode2D(3, 1, 'a');
	
	bst.insert(*x);
	bst.insert(*y);
	bst.insert(*z);
	bst.insert(*a);
	bst.insert(*y);

	printBST(bst);

	bst.remove(*y);

	x->setData('b');
	z->setData('b');
	a->setData('b');
	y->setData('b');

	printBST(bst);

	if (bst.getEntry(*x, x)) {
		cout << "Found x!\n";
	}
	else {
		cout << "Missing x!\n";
	}
	if (bst.getEntry(*y, y)) {
		cout << "Found y!\n";
	}
	else {
		cout << "Missing y!\n";
	}
	if (bst.getEntry(*z, z)) {
		cout << "Found z!\n";
	}
	else {
		cout << "Missing z!\n";
	}
	if (bst.getEntry(*a, a)) {
		cout << "Found a!\n";
	}
	else {
		cout << "Missing a!\n";
	}


	getchar();
    return 0;
}

void printBST(BinarySearchTree<GraphNode2D> &bst) {
	Queue<GraphNode2D*> aaa;

	bst.preOrder(aaa);

	cout << "Pre Order : \n";
	while (!aaa.isEmpty()) {
		GraphNode2D * a;
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << " " << a->Data() << endl;
	}
	
	cout << "\nIn Order:\n";
	bst.inOrder(aaa);

	while (!aaa.isEmpty()) {
		GraphNode2D * a;
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << " " << a->Data() << endl;
	}
	
	cout << endl;
}
