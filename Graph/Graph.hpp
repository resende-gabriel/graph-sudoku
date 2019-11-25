#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "Node.hpp"

using std::vector;

class Graph {
	public:
		vector<Node*> nodes;

		Graph();
		~Graph();
		/* adiciona uma aresta entre dois nos */
		void AddEdge(Node* orig, Node* dest);
		/* adiciona um no' no grafo */
		void AddNode(Node* n);
		/* retorna a quantidade de nos no grafo */
		int Size();
};

#endif