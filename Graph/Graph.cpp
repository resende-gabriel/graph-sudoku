#include "Graph.hpp"

Graph::Graph() {}

Graph::~Graph() {
	for (auto const& n : this->nodes) {
		delete n;
	}
}
		
Node* Graph::FindNode(vector<Node*> nodeList, Node* n) {
	if (n == nullptr) {
		return nullptr;
	}

	for (auto const& current : nodeList) {
		if(current->IsEqual(n)) {
			return current;
		}
	}
	return nullptr;
}

void Graph::AddNode(Node* n) {
	this->nodes.push_back(n);
}

void Graph::AddEdge(Node* orig, Node* dest) {
	if (orig->HasEdge(dest) || dest->HasEdge(orig)) {
		return;
	}

	orig->edgeNodes.push_back(dest);
	dest->edgeNodes.push_back(orig);
}

int Graph::Size() {
	return this->nodes.size();
}