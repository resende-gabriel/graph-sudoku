#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

class Cell {
	public:
		int column, line, value;
		Cell();
		Cell(int column, int line, int value);
		bool IsEqual(Cell* c);
};

#endif