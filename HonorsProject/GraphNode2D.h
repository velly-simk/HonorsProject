/*
	GraphNode2D
	not yet a template

	Fall 2017

	Velly Simeonov
*/

#pragma once
#ifndef GRAPHNODE2D_H
#define GRAPHNODE2D_H

class GraphNode2D {
private:
	char _data;
	int _x, _y, _nlink = 0;
	GraphNode2D * _links[4] = { nullptr };
	bool _processedFlag = false;

public:
	GraphNode2D() {
		_x = 0;
		_y = 0;
		_data = '0';
	}
	GraphNode2D(int x, int y, char data) {
		_x = x;
		_y = y;
		_data = data;
	}

	/* X coordinate. */
	int X() const { return _x; }

	/* Y coordinate. */
	int Y() const { return _y; }

	/* Char Data of node. */
	char Data() const { return _data; }

	void setData(const char &newData) { _data = newData; }

	bool getFlag() { return _processedFlag; }
	void setFlag(bool status) { _processedFlag = status; }

	/* Add node to links of this Node, returns true on success. */
	bool Link(GraphNode2D* &node);

	/* Removes node from links if it exist there, true on success.
	False if node does not exist in links.*/
	bool Delink(GraphNode2D * &node);

	/* Returns sorted array of 4 GraphNode Ptrs.
	Null Ptrs at end of array is not full.*/
	int Links(GraphNode2D ** &ret);

	GraphNode2D& operator=(const GraphNode2D& rhs) {
		_x = rhs.X();
		_y = rhs.Y();
		return *this;
	}
};

// comparison operators

bool operator< (GraphNode2D lhs, GraphNode2D rhs);

bool operator> (GraphNode2D lhs, GraphNode2D rhs);

bool operator<= (GraphNode2D lhs, GraphNode2D rhs);

bool operator>= (GraphNode2D lhs, GraphNode2D rhs);

bool operator== (GraphNode2D lhs, GraphNode2D rhs);

bool operator!= (GraphNode2D lhs, GraphNode2D rhs);

int compareGraphNode2D(GraphNode2D &lhs, GraphNode2D &rhs);


#endif // !2DGRAPHNODE_H
