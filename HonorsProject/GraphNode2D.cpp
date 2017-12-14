#include "GraphNode2D.h"

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

int compareGraphNode2D(GraphNode2D &lhs, GraphNode2D &rhs) {
	if (lhs > rhs) return 1;
	else if (rhs > lhs) return -1;
	else return 0;
}