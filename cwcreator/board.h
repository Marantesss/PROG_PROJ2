#ifndef board_h
#define board_h
#include <string>

using namespace std;

class Board {
public:
	Board(int &columns,int &lines); // Atualiza o numero de colunas de linhas
	int getColumns() const; // Devolve o numero de colunas
	int getLines() const; // Devolve o numero de linhas
	void showBoard(); // Da print ao tabuleiro
private:
	int columns; // Numero de colunas
	int lines; // Numero de linhas
};

#endif
