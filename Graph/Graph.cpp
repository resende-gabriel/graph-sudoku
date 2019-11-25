#include "Graph.hpp"

Graph::Graph() {}

Graph::~Graph() {
	for (auto const& n : this->nodes) {
		delete n;
	}
}

void Graph::AddNode(Node* n) {
	this->nodes.push_back(n);
}

void Graph::AddEdge(Node* orig, Node* dest) {
	// nao adiciona novamente caso os nos ja tenham uma aresta entre si
	if (orig->HasEdge(dest) || dest->HasEdge(orig)) {
		return;
	}

	orig->edgeNodes.push_back(dest);
	dest->edgeNodes.push_back(orig);
}

int Graph::Size() {
	return this->nodes.size();
}