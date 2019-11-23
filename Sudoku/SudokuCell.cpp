#include "SudokuCell.hpp"

Cell::Cell(int column, int line, int value) : column(column), line(line), value(value) {}

bool Cell::IsEqual(Cell* c) {
	return c->column == this->column && c->line == this->line && c->value == this->value;
}