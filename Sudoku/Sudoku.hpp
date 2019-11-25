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
		/* faz todos os passos necessarios para resolver o sudoku, retornando true caso tenha sido
		resolvido ou false caso contrario */
		bool Solve();
		/* adiciona arestas entre os nos que estao na mesma linha, coluna ou bloco */
		void AddEdges();
		/* percorre todos os nos do grafo, preenchendo um a um, ate o grafo ser totalmente
		preenchido */
		void FillGraph();
		/* retorna a quantidade de nos preenchidos no grafo */
		int FilledNodesCount();
		/* identifica o indice do no que e' mais facil de calcular o valor a ser inserido,
		com base nos valores dos nos vizinhos */
		int IndexToFill();
		/* retorna a quantidade de vizinhos preenchidos de um no, desconsiderando repeticoes de valores */
		int UniqueDegree(Node* n);
		/* retorna a quantidade total de vizinhos preenchidos de um no */
		int Degree(Node* n);
		/* retorna os valores unicos de nos vizinhos do no passado como parametro */
		map<int, bool> UniqueAdjacentValues(Node* n);
		/* retorna true caso um no estaja preenchido e false caso contrario */
		bool IsFilled(Node* n);
		/* preenche o no escolhido com base nos valores dos nos vizinhos */
		void FillCell(Node* n);
		/* retorna um vetor contendo a quantidade de ocorrencias de cada valor no grafo */
		int* ValuesCount();
		/* verifica se todos os nos foram preenchidos com valores validos */
		bool ValidateResult();
		/* exibe tabuleiro do sudoku */
		void Print();

};

#endif