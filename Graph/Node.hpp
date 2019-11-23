#ifndef NODE_H
#define NODE_H

#include <vector>
#include "../Sudoku/SudokuCell.hpp"

using std::vector;

class Node {
	public:
		Cell* c;
		vector<Node*> edgeNodes; // edges

		Node(Cell* cell);
		~Node();
		bool IsEqual(Node* n);
		bool HasEdge(Node* n);

};

#endif