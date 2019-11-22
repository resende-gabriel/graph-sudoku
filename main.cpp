#include <fstream>
#include <iostream>
#include "Graph/Graph.hpp"
#include "Sudoku/Sudoku.hpp"

using std::cout;
using std::endl;
using std::ifstream;

void readSpecs(int *size, int *blockHeight, int *blockWidth, ifstream& fs);
void readInputs(Graph* g, int size, ifstream& fs);

int main(int argc, char *argv[]) {

	ifstream fs;
	fs.open(argv[1]);
	int size, blockHeight, blockWidth;
	readSpecs(&size, &blockHeight, &blockWidth, fs);

	Graph* g = new Graph();
	readInputs(g, size, fs);

	Sudoku* s = new Sudoku(blockHeight, blockWidth, size, g);
	s->Print();


	if (s->Solve()) {
		cout << "sem solucao" << endl;
		return 0;
	}

	cout << "solucao" << endl;
	s->Print();
	delete s;

	return 0;
}

void readSpecs(int *size, int *blockHeight, int *blockWidth, ifstream& fs) {
	fs >> *size >> *blockHeight >> *blockWidth;
}

void readInputs(Graph* g, int size, ifstream& fs) {
	int value;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fs >> value;
			g->AddNode(new Node(new Cell(j, i, value)));
		}
	}
}