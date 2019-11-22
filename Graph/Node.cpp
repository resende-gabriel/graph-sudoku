#include "Node.hpp"

Node::Node(Cell* cell) : c(cell) {};

Node::~Node() {
	delete this->c;
}

bool Node::IsEqual(Node* n) {
	return this->c->IsEqual(n->c);
}

bool Node::Contains(Node* n) {
	if (n == nullptr) {
		return false;
	}

	for (auto const& current : this->edgeNodes) {
		if(current->IsEqual(n)) {
			return true;
		}
	}
	return false;
}

bool Node::Contains(Cell* c) {
	if (c == nullptr) {
		return false;
	}

	for (auto const& current : this->edgeNodes) {
		if(current->c->IsEqual(c)) {
			return true;
		}
	}
	return false;
}
