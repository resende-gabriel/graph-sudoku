#include <fstream>
#include <iostream>
#include "Graph/Graph.hpp"
#include "Sudoku/Sudoku.hpp"

using std::cout;
using std::endl;
using std::ifstream;

// le as informacoes do arquivo passado como argumento, inserindo os valores em um grafo
void readInputs(int *size, int *blockHeight, int *blockWidth, Graph* g, ifstream& fs);

int main(int argc, char *argv[]) {

	ifstream fs;
	fs.open(argv[1]);
	if (!fs.is_open()) {
		return 0;
	}
	int size, blockHeight, blockWidth;
	Graph* g = new Graph();
	readInputs(&size, &blockHeight, &blockWidth, g, fs);

	Sudoku* s = new Sudoku(blockHeight, blockWidth, size, g);

	if (!s->Solve()) {
		cout << "sem solução" << endl;
	} else {
		cout << "solução" << endl;
	}
	s->Print();
	delete s;
	return 0;
}


void readInputs(int *size, int *blockHeight, int *blockWidth, Graph* g, ifstream& fs) {
	int value;
	fs >> *size >> *blockWidth >> *blockHeight;
	for (int line = 0; line < *size; line++) {
		for (int column = 0; column < *size; column++) {
			fs >> value;
			g->AddNode(new Node(new Cell(column, line, value)));
		}
	}
}