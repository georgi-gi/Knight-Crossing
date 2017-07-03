#include <iostream>
#include <queue>
#include <vector>
#include "Node.h"

//all the moves the knight can do and the position movement by row and column for each one
const int numberOfMoves = 8;
const signed char deltaRow[numberOfMoves] = { -2,-1,1,2,2,1,-1,-2 };
const signed char deltaCol[numberOfMoves] = { -1,-2,-2,-1,1,2,2,1 };

//for a given node adds all the possible moves to the priority queue with the corresponding priority
void expandNode(Node* node, std::priority_queue<Node*, std::vector<Node*>, MyComparator>* pq,
	bool **discovered, int boardSize) {

	for (size_t i = 0; i < numberOfMoves; ++i) {
		int newRow = node->row + deltaRow[i];
		int newCol = node->col + deltaCol[i];
		if (newRow < 1 || newRow > boardSize || newCol < 1 || newCol > boardSize
			|| discovered[newRow-1][newCol-1]) {
			continue;
		}
		Node* newNode = new Node(node->pathLen + 1,
			newRow,
			newCol,
			node,
			boardSize);
		pq->push(newNode);
	}
	return;
}

//main algorithm
Node* AStar(Node* start, std::priority_queue<Node*, std::vector<Node*>, MyComparator>* pq,
	std::vector<Node*>* toDelete, int boardSize) {

	bool** discovered = new bool*[boardSize];
	for (size_t i = 0; i < boardSize; ++i) {
		discovered[i] = new bool[boardSize];
	}

	for (size_t i = 0; i < boardSize; ++i) {
		for (size_t j = 0; j < boardSize; ++j) {
			discovered[i][j] = false;
		}
	}

	while (!pq->empty()) {
		Node* current = pq->top();
		if (discovered[current->row - 1][current->col - 1]) {
			toDelete->push_back(current);
			pq->pop();
		}
		if (current->row == boardSize && current->col == boardSize) {
			toDelete->push_back(current);
			pq->pop();

			for (size_t i = 0; i < boardSize; ++i) {
				delete[] discovered[i];
			}
			delete[] discovered;

			return current;
		}
		toDelete->push_back(current);
		pq->pop();
		expandNode(current, pq, discovered, boardSize);
		discovered[current->row - 1][current->col - 1] = true;
	}

	//free discovered array
	for (size_t i = 0; i < boardSize; ++i) {
		delete[] discovered[i];
	}
	delete[] discovered;
	return nullptr;
}

int main() {
	std::cout << "Enter board size: ";
	int boardSize = 0;
	std::cin >> boardSize;

	Node* root = new Node(0, 1, 1, nullptr, boardSize);

	std::priority_queue<Node*, std::vector<Node*>, MyComparator> pq;
	pq.push(root);

	//vector with Nodes that are already discovered but not deleted so that we can
	//construct the path later
	//will be deleted after that
	std::vector<Node*> toDelete;

	Node* result = AStar(root, &pq, &toDelete, boardSize);

	//construct path
	if (result) {
		std::vector<Node*> path;
		while(result->parentNode) {
			path.push_back(result);
			result = result->parentNode;
		}

		//print shortest path
		std::cout << path.size() << '\n';
		std::cout << "The shortest path from (1,1) to (" << boardSize << ',' << boardSize << ") is:\n(1,1)\n";
		while (!path.empty()) {
			std::cout << '(' << path.back()->row << ',' << path.back()->col << ")\n";
			path.pop_back();
		}
	}
	else {
		std::cout << "Not possible.\n";
	}
	
	//free allocated memory
	while (!toDelete.empty()) {
		delete toDelete.back();
		toDelete.pop_back();
	}
	/*while (!pq.empty()) {
		delete pq.top();
		pq.pop();
	}*/

	return 0;
}