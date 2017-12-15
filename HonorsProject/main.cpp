/*
	CIS 22C Honors Project main entry point

	Fall 2017

	Velly Simeonov
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <ctime>

#include "Graph2D.h"

using namespace std;

void printAVL(AVLTree<GraphNode2D> &avl);
void parseGraph(Graph2D &graph, char ** &picture, int xSize, int ySize);

int _recursiveTrace(char** picture, int posX, int posY);
void printObjects(Queue<Queue<GraphNode2D*>*> queue);

int main(int argc, char *argv[])
{
	ifstream inFile;
	inFile.open("t0.txt", ifstream::in);
	char ** inputArr = nullptr, **inputArrCpy = nullptr;
	int x, y;
	Graph2D graph;
	clock_t time;
	double duration;
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
		inputArrCpy = new char*[y];
		for (int i = 0; i < y; ++i)
			inputArrCpy[i] = new char[x];


		// parse lines
		for (int i = 0; i < y; ++i) {
			getline(inFile, tmp);
			for (int j = 0; j < x; ++j) {
				inputArr[i][j] = tmp.at(j);
				inputArrCpy[i][j] = tmp.at(j);
			}
		}
		inFile.close();
	}
	int num = 0;
	time = clock();
	for (int j = 0; j < y; ++j) {
		for (int i = 0; i < x; ++i) {
			if (inputArr[j][i] != '0') {
				++num;
				/*int obj =*/ _recursiveTrace(inputArr, i, j);
				//cout << "Object of size : " << obj << endl;
			}
		}
	}
	duration = (clock() - time) / (double) CLOCKS_PER_SEC;

	cout << "Recursive parse time : " << duration << endl;
	cout << "Number of Objects : " << num << endl;

	time = clock();
	parseGraph(graph, inputArrCpy, x, y);
	duration = (clock() - time) / (double)CLOCKS_PER_SEC;

	cout << "Graph parse time : " << duration << endl;

	time = clock();
	Queue<Queue<GraphNode2D*>*>* queue = graph.objects();
	duration = (clock() - time) / (double)CLOCKS_PER_SEC;
	
	cout << "Object parse from graph time : " << duration << endl;

	cout << "Number of Objects :" << queue->getCount() << endl;

//	printObjects(*queue);
/*
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			cout << inputArr[i][j] << " ";
		}
		cout << endl;
	}
	*/

	//Clean up
	while (!queue->isEmpty()) {
		Queue<GraphNode2D*> *tmp;
		queue->dequeue(tmp);
		delete tmp;
	}
	delete queue;
	
	for (int i = 0; i < y; ++i) {
		delete inputArr[i];
		delete inputArrCpy[i];
	}

	delete inputArr;
	delete inputArrCpy;

	
	// 2D Graph avl tree fails to deconstruct, has something to do with objects() method not properly copying the tree?
	// need to also delete GraphNode2D but apparently they have been lost
	getchar();
    return 0;
}

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

void parseGraph(Graph2D &graph, char ** &picture, int xSize, int ySize) {
	bool linking = false;
	GraphNode2D *ptr, *last = nullptr;

	for (int i = 0; i < ySize; ++i) {
		for (int j = 0; j < xSize; ++j) {
			if (picture[i][j] == '0')
				linking = false;
			else {
				ptr = new GraphNode2D(j, i, picture[i][j]);
				if (linking) {
					last->Link(ptr);
					ptr->Link(last);
				}
				last = ptr;
				graph.insert(*ptr);
				linking = true;
			}
		}
	}
	linking = false;

	for (int i = 0; i < xSize; ++i) {
		for (int j = 0; j < ySize; ++j) {
			if (picture[j][i] == '0')
				linking = false;
			else {
				ptr = graph.getNode(GraphNode2D(i, j, picture[j][i]));
				if (linking) {
					last->Link(ptr);
					ptr->Link(last);
				}
				last = ptr;
				linking = true;
			}
		}
	}


}

void printObjects(Queue<Queue<GraphNode2D*>*> queue) {
	Queue<GraphNode2D*> * object;
	GraphNode2D * val;
	while (!queue.isEmpty()) {
		queue.dequeue(object);

		while (!object->isEmpty()) {
			object->dequeue(val);
			cout << val->Data();
		}
		cout << endl;
			
	}
}

int _recursiveTrace(char** picture, int posX, int posY) {
	if (picture[posY][posX] == '0')
		return 0;
	else {
		picture[posY][posX] = '0';
		return _recursiveTrace(picture, posX + 1, posY) +
			_recursiveTrace(picture, posX, posY + 1) +
			_recursiveTrace(picture, posX, posY - 1) +
			_recursiveTrace(picture, posX - 1, posY) + 1;
	}
}