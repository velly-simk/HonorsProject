#pragma once
#ifndef GRAPHNODE2D_H
#define GRAPHNODE2D_H

class GraphNode2D {
private:
	int x_coord, y_coord;
public:
	GraphNode2D(int x, int y) {
		x_coord = x;
		y_coord = y;
	}

	int X() const { return x_coord; }
	int Y() const { return y_coord; }

	GraphNode2D& operator=(const GraphNode2D& rhs) {
		x_coord = rhs.X();
		y_coord = rhs.Y();
		return *this;
	}
};


// comparison operators

bool operator< (GraphNode2D lhs, GraphNode2D rhs) {
	if (lhs.Y() == rhs.Y())	return lhs.X() < rhs.X();
	return lhs.Y() < rhs.Y();
}

bool operator> (GraphNode2D lhs, GraphNode2D rhs) { return rhs < lhs; }

bool operator<= (GraphNode2D lhs, GraphNode2D rhs) { return !(lhs > rhs); }

bool operator>= (GraphNode2D lhs, GraphNode2D rhs) { return !(lhs < rhs); }

bool operator== (GraphNode2D lhs, GraphNode2D rhs) {
	if (lhs.Y() == rhs.Y())	return lhs.X() == rhs.X();
	return false;
}

bool operator!= (GraphNode2D lhs, GraphNode2D rhs) { return !(lhs == rhs); }



#endif // !2DGRAPHNODE_H
