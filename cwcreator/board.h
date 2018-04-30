#ifndef board_h
#define board_h
#include <string>
#include <vector>


using namespace std;

class Board {
public:
	Board(int columns,int lines); // Atualiza o numero de colunas de linhas
	int getColumns() const; // Devolve o numero de colunas
	int getLines() const; // Devolve o numero de linhas
	void showBoard(); // Da print ao tabuleiro
private:
	int numColumns; // Numero de colunas
	int numLines; // Numero de linhas
	vector<vector<char>> board;

};

#endif
