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
		vector<Cell*> FillGraph();
		void FillCell(Node* n, vector<Cell*> filledCells, unsigned int* maxValue);
		map<int, bool> AdjacentValues(Node* n, vector<Cell*> filledCells);
		int SaturationDegree(Node* n, vector<Cell*> filledCells);
		bool IsFilled(Node* n, vector<Cell*> filledCells);
		int Degree(Node* n);
		bool Solve();
		// void AddNodes(Graph* g);
		void AddEdges();
		bool ValidateResult(vector<Cell*> result);
		void Print();

};

#endif