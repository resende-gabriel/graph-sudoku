#include "Node.hpp"

Node::Node(Cell* cell) : c(cell) {};

Node::~Node() {
	delete this->c;
}

bool Node::IsEqual(Node* n) {
	return this->c->IsEqual(n->c);
}

bool Node::HasEdge(Node* n) {
	if (n == nullptr) {
		return false;
	}

	for (auto const& edgeNode : this->edgeNodes) {
		if(edgeNode->IsEqual(n)) {
			return true;
		}
	}
	return false;
}