#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "Node.hpp"

using std::vector;

class Graph {
	public:
		Graph();
		~Graph();
		void InsertNode(int v);
		void AddEdge(Node* orig, Node* dest);
		void AddNode(Node* n);
		Node* FindNode(vector<Node*> nodeList, Node* n);
		vector<Node*> nodes;
		int Size();
};

#endif