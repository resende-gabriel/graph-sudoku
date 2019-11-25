#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

class Cell {
	public:
		const int column, line;
		int value;
		
		Cell(const int column, const int line, int value);
		/* retorna true caso o no' atual seja igual (possua os mesmos valores)
		do no' passado como parametro e false caso contrario */
		bool IsEqual(Cell* c);
};

#endif