#ifndef board_h
#define board_h
#include <string>
#include <vector>
#include <utility>
#include "dictionary.h"


using namespace std;

class Board {
public:
	Board(int lines, int columns); // Atualiza o numero de colunas de linhas
	int getColumns() const; // Devolve o numero de colunas
	int getLines() const; // Devolve o numero de linhas
	void showBoard(); // Da print ao tabuleiro
	void insertWord(string position, string word);
	void removeWord(string position);
	void finalizeBoard();
	void saveBoard(string dictionaryFileName);
	void saveFinalBoard(string dictionaryFileName);
	void loadBoard(string fileName);
	bool wordRepeated(string word); // Checks if an inserted word was already inserted before
private:
	int numColumns; // Numero de colunas
	int numLines; // Numero de linhas
	vector<vector<char>> board;
	vector<pair<string, string>> position_words;
	vector<char> upperLetters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	vector<char> lowerLetters = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	vector<pair<int, int>> nonRemovableLetters;
	bool wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word);
	bool wordMatchesSpace(int const &line, int const &column, char const &orientation, string const &word);
	int getIndex(char letter);
	bool isInNonRemovable(int line, int colunms);
	vector<char> loadBoardLine(string &line);
	int boardNameCounter = 1; // Contador do numero de tabuleiros que foram criados num run
};

#endif
