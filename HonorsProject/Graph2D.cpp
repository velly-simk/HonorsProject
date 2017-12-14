#include "Graph2D.h"

bool Graph2D::insert(GraphNode2D &input) {
	if (nodes.insert(input)) {
		++_nodeCount;
		return true;
	}
	return false;
}
bool Graph2D::remove(GraphNode2D &input) {
	if (nodes.remove(input)) {
		--_nodeCount;
		return true;
	}
	return false;
}

GraphNode2D* Graph2D::getNode(GraphNode2D &node) {
	GraphNode2D * tmp;
	nodes.getEntry(node, tmp);
	return tmp;
}

Queue<Queue<GraphNode2D*>*> Graph2D::breadthOrder() {
	Queue<Queue<GraphNode2D*>*> outQueue;

	Queue<GraphNode2D*> * objectQueue;

	Queue<GraphNode2D*> intermediary;

	AVLTree<GraphNode2D> allNodes = nodes; // copy AVL tree
	GraphNode2D *tmp;

	allNodes.getLeftMost(tmp); // get pointer to least value

	GraphNode2D ** links;
	int nlinks;
	bool startFlag = tmp->getFlag();

	while (!allNodes.isEmpty()) { // while there are still nodes
		intermediary.enqueue(tmp); // start an object
		objectQueue = new Queue<GraphNode2D*>();

		while (!intermediary.isEmpty()) { // parse object
			allNodes.remove(*tmp); // remove node from all nodes
			intermediary.dequeue(tmp); // remove from queue

			tmp->setFlag(!startFlag); // toggle flag

			objectQueue->enqueue(tmp);

			nlinks = tmp->Links(links); // get links data
			for (int i = 0; i < nlinks; ++i) { // parse links into object queue
				if (links[i]->getFlag() == startFlag) { // do not include parsed links
					intermediary.enqueue(links[i]);
				}
			}
			outQueue.enqueue(objectQueue); // que object into output
		}
	}

	return outQueue;
}