#pragma once
class Node {
public:
	int heuristicsValue;
	int pathLen;
	size_t row;
	size_t col;
	Node* parentNode;
public:
	Node(int pathLen, int row, int col, Node* parent, int size);
	bool operator<(const Node& rhs) const;
};

Node::Node(int pathLen, int row, int col, Node* parent, int size) {
	heuristicsValue = row >= col ?
		size - col + pathLen : 
		size - row + pathLen;
	this->pathLen = pathLen;
	this->row = row;
	this->col = col;
	parentNode = parent;
}

bool Node::operator<(const Node& rhs) const {
	return (this->heuristicsValue > rhs.heuristicsValue);	//want node with least heuristics value first
}

struct MyComparator {
	bool operator() (Node* arg1, Node* arg2) {
		return *arg1 < *arg2; //calls the operator
	}
};