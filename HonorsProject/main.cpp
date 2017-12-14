/*
	CIS 22C Honors Project main entry point

	Fall 2017

	Velly Simeonov
*/

#include <iostream>

#include "Graph2D.h"
#include "AVLTree.h"

using namespace std;

//void printBST(BinarySearchTree<GraphNode2D> &bst);
void printAVL(AVLTree<GraphNode2D> &avl);


int main(int argc, char *argv[])
{
	GraphNode2D* x = new GraphNode2D(1, 1, 'a'),
		*y = new GraphNode2D(1, 2, 'a'),
		*z = new GraphNode2D(2, 1, 'a'),
		*a = new GraphNode2D(3, 1, 'a');

	AVLTree<GraphNode2D> avl = AVLTree<GraphNode2D>(compareGraphNode2D, true);

	avl.insert(*x);
	avl.insert(*y);
	avl.insert(*z);
	avl.insert(*a);
	avl.insert(*y);
	avl.insert(*z);
	avl.insert(*a);
	avl.insert(*y);
	avl.insert(*x);
	avl.insert(*y);
	avl.insert(*z);


	printAVL(avl);
	avl.printTree();


	avl.remove(*z);
	printAVL(avl);
	avl.printTree();

	getchar();
    return 0;
}
/*
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
*/
void printAVL(AVLTree<GraphNode2D> &avl) {
	Queue<GraphNode2D*> aaa;
	GraphNode2D * a;

	avl.preOrder(aaa);

	cout << "Pre Order : \n";
	while (!aaa.isEmpty()) {
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << " " << a->Data() << endl;
	}

	cout << "\nIn Order:\n";
	avl.inOrder(aaa);

	while (!aaa.isEmpty()) {
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << " " << a->Data() << endl;
	}

	avl.breadthOrder(aaa);

	cout << "\nBreadth Order : \n";
	while (!aaa.isEmpty()) {
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << " " << a->Data() << endl;
	}


	cout << endl;
}
