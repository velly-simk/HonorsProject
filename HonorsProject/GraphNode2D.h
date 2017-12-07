#pragma once
#ifndef GRAPHNODE2D_H
#define GRAPHNODE2D_H

class GraphNode2D {
private:
	char _data;
	int _x, _y, _nlink = 0;
	GraphNode2D * _links[4] = { nullptr };
	bool _processed = false;

public:
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


// Public functions
bool GraphNode2D::Link(GraphNode2D* &node) {
	if (_nlink < 4) { // max links is 4
		_links[_nlink++] = node;
		return true;
	}
	return false;
}

// nullptrs are always at end, changing this means changing link() and links() as well
bool GraphNode2D::Delink(GraphNode2D* &node) {
	if (_nlink > 0) {
		for (int i = 0; i < 4; ++i) { // max links is 4;
			if (_links[i] == node) {
				for (int x = i; x < 3; ++x) { // shift links if node is not last
					_links[x] = _links[x + 1];
				}
				_links[3] = nullptr; // set last
				--_nlink;
				return true;
			}
		}
	}
	return false;
}

int GraphNode2D::Links(GraphNode2D ** &ret) {
	ret = _links;
	
	for (int i = 0; (ret[i] != nullptr) && (i < _nlink); ++i) { // selection sort until first nullptr
		GraphNode2D ** tmp = &ret[i];

		for (int x = i + 1; x < _nlink; ++x) { // find smallest
			if ((ret[x] != nullptr) && ((*ret[x]) < (**tmp))) tmp = &ret[x];
		}

		// swap regardless of tmp == ret[i], faster than a check 
		GraphNode2D * tmp2;
		tmp2 = *tmp;
		ret[tmp - ret] = ret[i];
		ret[i] = tmp2;
	}

	return _nlink;
}



#endif // !2DGRAPHNODE_H
