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
	void insertWord(string position, string word);
	bool wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word);
	bool wordMatchesSpace(int const &line, int const &column, char const &orientation, string const &word);
	int getNumber(char letter);
private:
	int numColumns; // Numero de colunas
	int numLines; // Numero de linhas
	vector<vector<char>> board;
	vector<char> upperLetters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	vector<char> lowerLetters = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
};

#endif
