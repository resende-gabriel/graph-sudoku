#include "Sudoku.hpp"
#include <map>

using std::map;

Sudoku::Sudoku(const int bh, const int bw, const int s, Graph* g) : blockHeight(bh), blockWidth(bw), size(s), g(g) {}

Sudoku::~Sudoku() {
	delete this->g;
}

/* enquanto a quantidade de nos preenchidos for menor que a quantidade de nos no grafo,
preenche um no por vez considerando a posicao mais facil de identificar o valor a ser inserido */ 
void Sudoku::FillGraph() {
	for (int filledNodes = this->FilledNodesCount(); filledNodes < this->g->Size(); filledNodes++) {
		this->FillCell(this->g->nodes[this->IndexToFill()]);   
	}
}

int Sudoku::FilledNodesCount() {
	int count = 0;
	for (auto const& n : this->g->nodes) {
		if(this->IsFilled(n)) {
			count++;
		}
	}
	return count;
}

/* busca o no que possui o maior numero de vizinhos preenchidos, considerando primeiro
a quantidade de valores unicos nos vizinhos, e usando a quantidade de valores nao unicos
como desempate */
int Sudoku::IndexToFill() {
	int max = -1, index = -1;
	for (int i = 0; i < this->g->Size(); i++) {
		if (this->IsFilled(this->g->nodes[i])) {
			continue;
		}
		int degree = this->UniqueDegree(this->g->nodes[i]);
		if (degree > max) {
			max = degree;
			index = i;
			continue;
		}
		if (degree != max) {
			continue;
		}
		if (this->Degree(this->g->nodes[index]) < this->Degree(this->g->nodes[i])) {
			index = i;
		}
	}
	return index;
}

void Sudoku::FillCell(Node* n) {
	map<int, bool> adjacentValues = this->UniqueAdjacentValues(n);

	// se a quantidade de valores unicos dos vizinhos for maior ou igual a n, o sudoku ja
	// estara' errado, e nao ha' como descobrir um valor valido para o no'
	if (adjacentValues.size() >= (unsigned int)this->size) {
		n->c->value = this->size+1;
		return;
	}

	// lista os valores que podem ser usados para preencher o no' atual
	vector<int> availableValues;
	for (int i = 1; i <= this->size; i++) {
		if (!adjacentValues[i]) {
			availableValues.push_back(i);
		}
	}

	if (availableValues.size() == 0) {
		n->c->value = this->size+1;
		return;
	}

	if (availableValues.size() == 1) {
		n->c->value = availableValues[0];
		return;
	}

	// se houver mais de um valor disponivel, escolhe o que tem mais ocorrencias
	// no grafo
	int* valuesCount = this->ValuesCount();
	int maxVal = 0, finalValue = 0;
	for (unsigned int i = 0; i < availableValues.size(); i++) {
		if (valuesCount[availableValues[i]] > maxVal) {
			finalValue = availableValues[i];
			maxVal = valuesCount[availableValues[i]];
		}
	}

	delete valuesCount;
	n->c->value = finalValue;
}

int* Sudoku::ValuesCount() {
	int *valuesCount = new int[this->size+1];
	for (int i = 0; i < this->size+1; i++) {
		valuesCount[i] = 0;
	}
	for (auto const& n : this->g->nodes) {
		if (this->IsFilled(n) && n->c->value <= this->size) {
			valuesCount[n->c->value]++;
		}
	}
	return valuesCount;
}

map<int, bool> Sudoku::UniqueAdjacentValues(Node* n) {
	// utiliza um mapa para evitar que valores ja inseridos sejam inseridos novamente
	map<int, bool> adjacentValues;
	for (auto const& adj : n->edgeNodes) {
		if (this->IsFilled(adj)) {
			adjacentValues[adj->c->value] = true;
		}
	}
	return adjacentValues;
}

int Sudoku::UniqueDegree(Node* n) {
	return this->UniqueAdjacentValues(n).size();
}

int Sudoku::Degree(Node* n) {
	int filledAdjNodes = 0;
	for (auto const& adj : n->edgeNodes) {
		if (this->IsFilled(adj)) {
			filledAdjNodes++;
		}
	}
	return filledAdjNodes;
}

bool Sudoku::IsFilled(Node* n) {
	return n->c->value != 0;
}

bool Sudoku::Solve() {
	this->AddEdges();
	this->FillGraph();
	return this->ValidateResult();
}

void Sudoku::AddEdges() {
	int index, currentIndex, blockStartH, blockStartW, blockIndex, startBlockIndex;

	// como os nos sao armazenados sequencialmente, devem ser feitos calculos para
	// identificar quais estao na mesma linha, coluna ou bloco
	for (auto const& n : this->g->nodes) {

		// calcula o inicio do bloco no qual o no atual esta contido
		blockStartH = n->c->line - n->c->line % this->blockHeight;
		blockStartW = n->c->column - n->c->column % this->blockWidth;
		blockIndex = blockStartW + blockStartH * this->size;
		startBlockIndex = blockIndex;
		currentIndex = n->c->column + n->c->line * this->size;
		
		// itera n vezes para pegar os outros n-1 elementos que estao na mesma linha/coluna/bloco 
		for (int j = 0; j < this->size; j++) {
			index = j + n->c->line * this->size;
			if (index != currentIndex) {
				g->AddEdge(n, g->nodes[index]);
			}

			index = n->c->column + j * this->size;
			if (index != currentIndex) {
				g->AddEdge(n, g->nodes[index]);
			}

			// se o contador atingir a largura do bloco, avanca 1 linha e recua para a coluna inicial
			if (blockIndex != startBlockIndex && blockIndex % this->blockWidth == 0) {
				blockIndex = blockIndex + this->size - this->blockWidth;
			}

			index = blockIndex;
			if (index != currentIndex) {
				g->AddEdge(n, g->nodes[index]);
			}
			blockIndex++;
		}
	}
}

bool Sudoku::ValidateResult() {
	for (auto const& n : this->g->nodes) {
		// se uma celula possui valor igual a 0 ou maior que n, ela e' invalida, portanto,
		// a solucao do sudoku tambem e' invalida
		if (n->c->value == 0 || n->c->value > this->size) {
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
