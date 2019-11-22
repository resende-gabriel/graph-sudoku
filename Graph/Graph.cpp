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

bool Graph::Contains(vector<Node*> nodeList, Node* n) {
	return this->FindNode(nodeList, n) != nullptr;
}

void Graph::AddNode(Node* n) {
	this->nodes.push_back(n);
}

void Graph::AddEdge(Node* orig, Node* dest) {
	Node* o = this->FindNode(this->nodes, orig);
	Node* d = this->FindNode(this->nodes, dest);

	if (o == nullptr || d == nullptr) {
		return;
	}

	if (o->Contains(d) || d->Contains(o)) {
		return;
	}

	o->edgeNodes.push_back(d);
	d->edgeNodes.push_back(o);
}

int Graph::Size() {
	return this->nodes.size();
}