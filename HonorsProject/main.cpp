/*
	CIS 22C Honors Project main entry point

	Fall 2017

	Velly Simeonov
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include "Graph2D.h"

using namespace std;

void printAVL(AVLTree<GraphNode2D> &avl);

int main(int argc, char *argv[])
{
	ifstream inFile;
	inFile.open("t4.txt", ifstream::in);
	char ** inputArr = nullptr;
	int x, y;

	/* transform file into 2D array of characters*/
	if (inFile.is_open()) {
		string tmp;
		size_t offs;
		// get x and y size
		getline(inFile, tmp);
		y = stoi(tmp, &offs, 10);
		tmp = tmp.substr(offs);
		x = stoi(tmp, NULL, 10);

		// allocate memory
		inputArr = new char*[y];
		for (int i = 0; i < y; ++i)
			inputArr[i] = new char[x];

		// parse lines
		for (int i = 0; i < y; ++i) {
			getline(inFile, tmp);
			for (int j = 0; j < x; ++j) {
				inputArr[i][j] = tmp.at(j);
			}
		}
		inFile.close();
	}


	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			cout << inputArr[i][j] << " ";
		}
		cout << endl;
	}
	/*
	const int x_size = 10, y_size = 10;
	GraphNode2D arr[y_size][x_size];
	AVLTree<GraphNode2D> avl = AVLTree<GraphNode2D>(compareGraphNode2D);
	
	for (int y = 0; y < y_size; ++y) {
		for (int x = 0; x < x_size; ++x) {
			arr[y][x] = GraphNode2D(x, y, 'b');
			avl.insert(arr[y][x]);
		}
	}

	printAVL(avl);
	avl.printBreadthOrderDepths();
	*/
	getchar();
    return 0;
}

void printAVL(AVLTree<GraphNode2D> &avl) {
	Queue<GraphNode2D*> aaa;
	GraphNode2D * a;
/*
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
	*/
	avl.breadthOrder(aaa);

	cout << "\nBreadth Order : \n";
	while (!aaa.isEmpty()) {
		aaa.dequeue(a);
		cout << a->X() << " " << a->Y() << " " << a->Data() << endl;
	}


	cout << endl;
}
