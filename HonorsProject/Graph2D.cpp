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

Queue<Queue<GraphNode2D*>*>* Graph2D::objects() {
	AVLTree<GraphNode2D> all = nodes;
	Queue<GraphNode2D*> *object;
	Queue<Queue<GraphNode2D*>*>* output = new Queue<Queue<GraphNode2D*>*>();
	GraphNode2D* piece;

	all.getLeftMost(piece);
	while (piece != nullptr && !all.isEmpty()) {
		object = new Queue<GraphNode2D*>;
		_recursiveTrace(piece, all, object);
		output->enqueue(object);
		all.getLeftMost(piece);
	}
	return output;
}

int Graph2D::_recursiveTrace(GraphNode2D *node, AVLTree<GraphNode2D> &list, Queue<GraphNode2D*> *&object) {
	if (node == nullptr || node->getFlag() == true) {
		return 0;
	}
	list.remove(*node);
	object->enqueue(node);
	node->setFlag(true);
	GraphNode2D **links;
	node->Links(links);
	return _recursiveTrace(links[0], list, object) + _recursiveTrace(links[1], list, object)
		+ _recursiveTrace(links[2],list, object) + _recursiveTrace(links[3], list, object) + 1;


}