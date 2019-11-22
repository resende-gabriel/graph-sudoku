#include "Sudoku.hpp"
#include <map>

using std::map;

Sudoku::Sudoku(const int bh, const int bw, const int s, Graph* g) : blockHeight(bh), blockWidth(bw), size(s), g(g) {}

Sudoku::~Sudoku() {
	delete this->g;
}

vector<Cell*> Sudoku::FillGraph() {
	vector<Cell*> result;
	unsigned int maxValue = 1;

	for (int filledNodes = 0; filledNodes < this->g->Size(); filledNodes++) {
		int max = -1, index = -1;

		for (int i = 0; i < this->g->Size(); i++) {
			if (IsFilled(this->g->nodes[i], result)) {
				continue;
			}
			int degree = SaturationDegree(this->g->nodes[i], result);
			if (degree > max) {
				max = degree;
				index = i;
				continue;
			}
			if (degree != max) {
				continue;
			}
			if (Degree(this->g->nodes[index]) < Degree(this->g->nodes[i])) {
				index = i;
			}
		}

		FillCell(this->g->nodes[index], result, &maxValue);   
	}
	return result;
}

void Sudoku::FillCell(Node* n, vector<Cell*> filledCells, unsigned int* maxValue) {
	map<int, bool> adjacentValues = this->AdjacentValues(n, filledCells);

	if (adjacentValues.size() == *maxValue) {
		maxValue++;
		n->c->value = *maxValue;
		filledCells.push_back(n->c);
		return;
	}
	// var colorNum = usedColors.Where(c => !colors.Contains(c)).OrderByDescending(c => nodeSet.Count(n => n.Color == c)).First();

	for (unsigned int i = 0; i < *maxValue; i++) {
		if (adjacentValues[i]) {
			continue;
		}

	}


	n->c->value = *maxValue;
	filledCells.push_back(n->c);
}

map<int, bool> Sudoku::AdjacentValues(Node* n, vector<Cell*> filledCells) {
	map<int, bool> values;
	for (auto const& c : filledCells) {
		if (n->Contains(c)) {
			values[c->value] = true;
		}
	}
	return values;
}

int Sudoku::SaturationDegree(Node* n, vector<Cell*> filledCells) {
	map<int, bool> adjacentValues;
	for (auto const& c : filledCells) {
		if (n->Contains(c)) {
			adjacentValues[c->value] = true;
		}
	}
	return adjacentValues.size();
}

bool Sudoku::IsFilled(Node* n, vector<Cell*> filledCells) {
	for (auto const& c : filledCells) {
		if (c->IsEqual(n->c)) {
			return true;
		}
	}
	return false;
}

int Sudoku::Degree(Node* n) {
	return n->edgeNodes.size();
}

bool Sudoku::Solve() {

	// this->AddNodes(g);
	this->AddEdges();

	for (auto const& n : this->g->nodes[10]->edgeNodes) {
		std::cout << n->c->column << " " << n->c->line << std::endl;
	}

	vector<Cell*> result = this->FillGraph();

	return this->ValidateResult(result);
}

// void Sudoku::AddNodes(Graph* g) {
//     for (int i = 0; i < this->size; i++) {
//         for (int j = 0; j < this->size; j++) {
//             Node* n = new Node(&this->cells[i][j]);
//             g->AddNode(n);
//         }
//     }
// }

void Sudoku::AddEdges() {
	int index, currentIndex, blockStartH, blockStartW, blockIndex, startBlockIndex;

	for (auto const& n : this->g->nodes) {

		blockStartH = n->c->line - n->c->line % this->blockHeight;
		blockStartW = n->c->column - n->c->column % this->blockWidth;
		blockIndex = blockStartW + blockStartH * this->size;
		startBlockIndex = blockIndex;
		currentIndex = n->c->column + n->c->line * this->size;
		
		for (int j = 0; j < this->size; j++) {
			index = j + n->c->line * this->size;
			std::cout << index << " ";
			if (index != currentIndex) {
				g->AddEdge(n, g->nodes[index]);
			}

			index = n->c->line + j * this->size;
			std::cout << index << " ";
			if (index != currentIndex) {
				g->AddEdge(n, g->nodes[index]);
			}

			if (blockIndex != startBlockIndex && blockIndex % this->blockWidth == 0) {
				blockIndex = blockIndex + this->size - this->blockWidth;
			}

			index = blockIndex;
			std::cout << index << " ";
			if (index != currentIndex) {
				g->AddEdge(n, g->nodes[index]);
			}
			blockIndex++;
		}
		std::cout << std::endl;
		
	}
}

bool Sudoku::ValidateResult(vector<Cell*> result) {
	if (result.size() < this->size * this->size) {
		return false;
	}
	for (auto const& cell : result) {
		if (cell->value == 0 || cell->value > this->size) {
			return false;
		}
	}
	return true;
}

void Sudoku::Print() {
	int index;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			index = i * this->size + j;
			cout << this->g->nodes[index]->c->value << " ";
		}
		cout << endl;
	}
	cout << endl;
}
