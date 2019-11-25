#ifndef NODE_H
#define NODE_H

#include <vector>
#include "../Sudoku/SudokuCell.hpp"

using std::vector;

class Node {
	public:
		Cell* c;
		// lista de nos que o no' atual tem uma aresta
		vector<Node*> edgeNodes;

		Node(Cell* cell);
		~Node();
		/* retorna true caso o no' atual seja igual (possua os mesmos valores)
		do no' passado como parametro e false caso contrario */
		bool IsEqual(Node* n);
		/* retorna true caso o no' atual tenha uma aresta com o no' passado
		por parametro e false caso contrario */
		bool HasEdge(Node* n);

};

#endif