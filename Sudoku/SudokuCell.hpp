#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

class Cell {
	public:
		const int column, line;
		int value;
		Cell(const int column, const int line, int value);
		bool IsEqual(Cell* c);
};

#endif