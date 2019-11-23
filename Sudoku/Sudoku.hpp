#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <map>
#include "../Graph/Graph.hpp"
#include "../Graph/Node.hpp"
#include "SudokuCell.hpp"

using std::cout;
using std::endl;
using std::map;
using std::vector;

class Sudoku {
	public:
		
		const int blockHeight, blockWidth, size;
		Graph* g;

		Sudoku(const int height, const int width, const int size, Graph* g);
		~Sudoku();
		void FillGraph();
		void FillCell(Node* n);
		map<int, bool> UniqueAdjacentValues(Node* n);
		int UniqueDegree(Node* n);
		bool IsFilled(Node* n);
		int Degree(Node* n);
		bool Solve();
		void AddEdges();
		bool ValidateResult();
		void Print();
		int* ValuesCount();
		int IndexToFill();
		int FilledNodesCount();

};

#endif