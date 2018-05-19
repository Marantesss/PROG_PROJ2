#ifndef board_h
#define board_h
#include <string>
#include <vector>
#include <utility>
#include "dictionary.h"


using namespace std;

class Board {
public:
	Board(int lines, int columns); // Update number of lines and columns
	int getColumns() const; // Returns the number of columns
	int getLines() const; // Returns the number of lines
	void showBoard(); // Prints the board
	void insertWord(string position, string word);
	void removeWord(string position);
	void finalizeBoard();
	void saveBoard(string dictionaryFileName);
	void saveFinalBoard(string dictionaryFileName);
	void loadBoard(string fileName);
	bool wordRepeated(string word); // Checks if an inserted word was already inserted before
	string getWildcardWord(string position); // Returns a pseudoword (with '?' and '*')
private:
	int numColumns; // Number of columns
	int numLines; // Number of lines
	vector<vector<char>> board;
	vector<pair<string, string>> position_words;
	vector<char> upperLetters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	vector<char> lowerLetters = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	vector<pair<int, int>> nonRemovableLetters;
	bool wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word);
	bool wordMatchesSpace(int const &line, int const &column, char const &orientation, string const &word);
	int getIndex(char letter);
	vector<pair<int, int>> findNonRemovableLetters(); // When the board is resumed, the non removable letters are found
	bool isInNonRemovable(int line, int colunms);
	vector<char> loadBoardLine(string &line);
	int boardNameCounter (); // board counter of the number of boards created
};

#endif
