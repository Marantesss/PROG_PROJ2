#include "board.h"
#include "puzzle.h"
#include "colors.h"
#include "puzzle.h"
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctype.h> // isalpha()
#include <iomanip>

Board::Board(int lines, int columns)
{
	numColumns = columns;
	numLines = lines;
	
	board.resize(numLines); // Resizes the vector 'board' to the user-entered number of lines
	for (int i = 0; i < numLines; i++)
		board[i].resize(numColumns);  //Resizes the vectors in the vector 'board' to the user - entered number of columns


	for (int i = 0; i < numLines; i++) // Fills the vector board with "."
		for (int j = 0; j < numColumns; j++)
			board.at(i).at(j) = '.';
}	

int Board::getColumns() const
{
	return numColumns;
}

int Board::getLines() const
{
	return numLines;
}

void Board::showBoard() 
{
	setcolor(12); // First line of letters is lightred
	for (int i = 0; i < numColumns + 1; i++)  // Prints the upper line with the column identifiers
		cout << lowerLetters.at(i) << "  ";   // stored in the vector lowerletters

	for (int i = 0; i < numLines; i++)
	{
		cout << endl;
		setcolor(12); // First column of letters is lightred
		cout << upperLetters.at(i) << "  ";  // Prints the identifier for each line
		for (int j = 0; j < numColumns; j++) {
			if (board.at(i).at(j) == '#') { // Checks if the char being printed is '#'
				setcolor(7, 0); // Change the color of the letters 7=LIGHTGRAY and background 0=BLACK
				cout << board.at(i).at(j);
				setcolor(0, 12);
				cout << "  "; // Prints each position of the board stored in board
			}
			else {
				setcolor(0, 12); // Change the color of the letters 0=BLACK and background 12=LIGTHRED
				cout << board.at(i).at(j) << "  "; // Prints each position of the board stored in board
			}
		}
	}
	cout << endl;
	setcolor(7, 0); // Change back to normal (7=LIGHTGRAY letters, 0=BLACK background)
}

void Board::insertWord(string position, string word)
{
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Changes the word to uppercase

	if (wordFitsSpace(line, column, orientation, word)) {
		if (!(wordMatchesSpace(line, column, orientation, word)))
			cerr << "The word does not match the space" << endl; // displays error message if the word does not match the space
		if (orientation == 'V' && wordMatchesSpace(line, column, orientation, word)) { // insert VERTICAL words, if the word matches the space
			if (line != 0)
				board.at(line - 1).at(column) = '#'; // If the word is not being inserted in the beginning of a column places a '#' in the position before
			for (int i = 0; i < word.length(); i++) {
				board.at(line).at(column) = word[i]; // inserts the word by changing the vector board
				line++;
			};
			if (line < getLines()) 
				board.at(line).at(column) = '#'; // If the word does not end in the last position of a column places a '#' in the next position
			position_words.push_back(make_pair(position, word)); // Adds a pair of (position - word) to a vector
		}

		if (orientation == 'H' && wordMatchesSpace(line, column, orientation, word)) { // insert HORIZONTAL words, if the word matches the space
			if (column != 0)
				board.at(line).at(column - 1) = '#'; // If the word is not being inserted in the beginning of a  places a '#' in the position before
			for (int i = 0; i < word.length(); i++) {
				board.at(line).at(column) = word[i]; // inserts the word by changing the vector board
				column++;
			};
			if (column < getColumns())
				board.at(line).at(column) = '#'; // If the word does not end in the last position of a line places a '#' in the next position
			position_words.push_back(make_pair(position, word)); // Adds a pair of (position - word) to a vector
		}
	}
	else
		cerr << "The word does not fit the space" << endl; // displays error message if the word does not fit the space
}

bool Board::wordRepeated(string word) // Checks if an inserted word was already inserted before
{
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Changes the word to uppercase
	for (int i = 0; i < position_words.size(); i++) // Removes the position and the word from the vector 
		if (position_words.at(i).second == word)
			return true;
	return false;
}

string Board::getWildcardWord(string position) // Returns a pseudoword(with '?' and '*')
{
	string pseudoWord;
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);
	if (orientation == 'V') {
		for (int i = line; i < board.size(); i++) { // Goes over all the elements in the line
			if (board.at(i).at(column) == '.')
				pseudoWord += "?";
			else
				pseudoWord += board.at(i).at(column);
		}
	}
	if (orientation == 'H') {
		for (int i = column; i < board.at(line).size(); i++) { // Goes over all the elements in the column
			if (board.at(line).at(i) == '.')
				pseudoWord += "?";
			else
				pseudoWord += board.at(line).at(i);
		}
	}

	return pseudoWord;
}

int Board::getIndex(char letter) // Gets the index of a given letter of line or column 
{
	return (int)letter - 65;
}

bool Board::wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word) 
// Checks if the word fits the column/line starting from the user entered position until the end of the column/line
{
	if (orientation == 'V')
	{
		if (getLines() - line >= word.length()) 
			return true;
		else return false;
	}
	if (orientation == 'H')
	{
		if (getColumns() - column >= word.length())
			return true;
		else return false;
	}	
}

bool Board::wordMatchesSpace(int const &line, int const &column, char const &orientation, string const &word)
// Checks if the word matches with the already in-board letters
{
	vector<pair<int, int>> temporaryNonRemovableLetters;
	int movingBoardVariable;
	if (orientation == 'V')  
	{
		movingBoardVariable = line;
		if (line != 0)
			if (board.at(movingBoardVariable - 1).at(column) != '.' && board.at(movingBoardVariable - 1).at(column) != '#') 
				return false; // If the char before is not '.' or '#' returns false
		if (movingBoardVariable + word.length() < getLines())
			if (board.at(movingBoardVariable + word.length()).at(column) != '.' && board.at(movingBoardVariable + word.length()).at(column) != '#')
				return false; // If the char after is not '.' or '#' returns false

		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(movingBoardVariable).at(column) != '.')  
			{
				if (board.at(movingBoardVariable).at(column) != toupper(word[i])) // If the word letter is different from the board letter returns false
					return false;
			}
			movingBoardVariable++;
		}
		return true;
	}
	
	if (orientation == 'H')
	{
		movingBoardVariable = column;
		if (column != 0)
			if (board.at(line).at(movingBoardVariable - 1) != '.' && board.at(line).at(movingBoardVariable - 1) != '#')
				return false;
		if (movingBoardVariable + word.length() < getLines())
			if (board.at(line).at(movingBoardVariable + word.length()) != '.' && board.at(line).at(movingBoardVariable + word.length()) != '#')
				return false;

		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(line).at(movingBoardVariable) != '.')
			{
				if (board.at(line).at(movingBoardVariable) != toupper (word[i]))
					return false;
			}
			movingBoardVariable++;
		}
		return true;
	}
}

void Board::removeWord(string position)
{
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);

	if (orientation == 'V') // VERTICAL words
	{
		if (line != 0) // If the word starts in the middle of the line changes the '#' to a '.'
			board.at(line - 1).at(column) = '.';
		
		while (board.at(line).at(column) != '#' && line < getLines()) 
		{
			board.at(line).at(column) = '.';
			line++;
			if (line == getLines()) // Stop the loop condition of trying to access beyond the length of the vector(error) 
				break;
		}
		if (line < getLines()) // If the word ends in the middle of the line changes the '#' to a '.'
			board.at(line).at(column) = '.';
	}

	if (orientation == 'H') // HORIZONTAL words
	{
		if (column != 0) // If the word starts in the middle of the column changes the '#' to a '.'
			board.at(line).at(column-1) = '.';

		while (board.at(line).at(column) != '#' && column < getColumns())
		{
			board.at(line).at(column) = '.';
			column++;
			if (column == getColumns()) // Stop the loop condition of trying to access beyond the length of the vector(error)
				break;
		}
		if (column < getColumns()) // If the word ends in the middle of the column changes the '#' to a '.'
			board.at(line).at(column) = '.';
	}
	for (int i = 0; i < position_words.size(); i++) // Removes the position and the word from the vector 
		if (position_words.at(i).first == position)
			position_words.erase(position_words.begin() + i);

	resetBoard();
}

void Board::finalizeBoard()
{
	for (int i = 0; i < getLines(); i++) // Fills the elements that are not letters or '#' with '#'
		for (int j = 0; j < getColumns(); j++)
			if (board.at(i).at(j) == '.')
				board.at(i).at(j) = '#';

}

int Board::boardNameCounter() // Returns the number of the board that has not yet been created
{
	int i = 0;
	ostringstream oss;

	while (true) {
		i++;
		oss << "b" << setfill('0') << setw(3) << i;
		oss << ".txt"; // oss = bxxx.txt

		ifstream boardFile(oss.str());
		boardFile.open(oss.str()); // Opens the file 

		if (!boardFile.is_open())
		{
			return i;
		}

		boardFile.close();
		oss.str(string()); // clears oss
	}
}

void Board::saveBoard(string dictionaryFileName) {
	ofstream boardFile;
	cout << "File will be saved into a text file (enter only the name of the file): ";

	string fileName;
	cin >> fileName;

	fileName += ".txt";
	boardFile.open(fileName);

	boardFile << dictionaryFileName << endl;

	for (int i = 0; i < numLines; i++) // Saves the (vector) board
	{
		boardFile << endl;
		for (int j = 0; j < numColumns; j++)
			boardFile << board.at(i).at(j) << "  ";
	}

	boardFile << endl;

	for (int i = 0; i < position_words.size(); i++) // Saves the position and the respective words
	{
		boardFile << endl;
		boardFile << position_words.at(i).first << " " << position_words.at(i).second;
	}
}

void Board::saveFinalBoard(string dictionaryFileName) // Same as saveBoard but the name is chosen by the user
{
	ostringstream oss; // oss is later converted to string
	int boardName = boardNameCounter();

	oss << "b" << setfill('0') << setw(3) << boardName;
	oss << ".txt"; // oss = bxxx.txt
	ofstream boardFile(oss.str());

	cout << "File will be saved into a text file..." << endl << endl;

	boardFile.open(oss.str()); // Opens the file 

	boardFile << dictionaryFileName << endl;

	for (int i = 0; i < numLines; i++) // Saves the (vector) board
	{
		boardFile << endl;
		for (int j = 0; j < numColumns; j++)
			boardFile << board.at(i).at(j) << "  ";
	}

	boardFile << endl;

	for (int i = 0; i < position_words.size(); i++) // Saves the position and the respective words
	{
		boardFile << endl;
		boardFile << position_words.at(i).first << " " << position_words.at(i).second;
	}
}

void Board::loadBoard(string fileName)
{
	ifstream boardFile;
	string line;

	boardFile.open(fileName);  // File to load 
	if (!boardFile.is_open())
		cout << "Couldn't open the file";

	// Dictionary file name is loaded in the outside of the class Board (in the class Puzzle)
	getline(boardFile, line);
	boardFile.seekg(line.length() + 4); // Moves the pointer to the line before of the beggining of the board
	
	getline(boardFile, line);

	while (!boardFile.eof()) // Loads the letters to the vector board
	{
		board.push_back(loadBoardLine(line)); // Loads a line of the board
		getline(boardFile, line);
		if (line == "\n" || line == "") // Stops when the board ends
			break;
	}
	
	while (!boardFile.eof()) { // Loads the positions and the words to a vector of pairs
		string position, word;
		getline(boardFile, line);
		
		position = line.substr(0, 3); // Position are the first 3 letters
		word = line.substr(4); // Words are the remaining letters

		position_words.push_back(make_pair(position, word)); // Makes a pair of (position-word)
	}
}

void Board::resetBoard() // Resets the board to empty, and then adds the word in vector position_words
{
	for (int i = 0; i < numLines; i++) // Fills the vector board with "."
		for (int j = 0; j < numColumns; j++)
			board.at(i).at(j) = '.';

	for (int i = 0; i < position_words.size(); i++) { // Writes the words on vector position_word
		insertWordBoard(position_words.at(i).first, position_words.at(i).second);
	}
}

void Board::insertWordBoard(string position, string word)
{
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Changes the word to uppercase

	if (wordFitsSpace(line, column, orientation, word)) {
		if (!(wordMatchesSpace(line, column, orientation, word)))
			cerr << "The word does not match the space" << endl; // displays error message if the word does not match the space
		if (orientation == 'V' && wordMatchesSpace(line, column, orientation, word)) { // insert VERTICAL words, if the word matches the space
			if (line != 0)
				board.at(line - 1).at(column) = '#'; // If the word is not being inserted in the beginning of a column places a '#' in the position before
			for (int i = 0; i < word.length(); i++) {
				board.at(line).at(column) = word[i]; // inserts the word by changing the vector board
				line++;
			};
			if (line < getLines())
				board.at(line).at(column) = '#'; // If the word does not end in the last position of a column places a '#' in the next position
		}

		if (orientation == 'H' && wordMatchesSpace(line, column, orientation, word)) { // insert HORIZONTAL words, if the word matches the space
			if (column != 0)
				board.at(line).at(column - 1) = '#'; // If the word is not being inserted in the beginning of a  places a '#' in the position before
			for (int i = 0; i < word.length(); i++) {
				board.at(line).at(column) = word[i]; // inserts the word by changing the vector board
				column++;
			};
			if (column < getColumns())
				board.at(line).at(column) = '#'; // If the word does not end in the last position of a line places a '#' in the next position
		}
	}
	else
		cerr << "The word does not fit the space" << endl; // displays error message if the word does not fit the space
}

vector<char> Board::loadBoardLine(string &line)
{
	vector<char> boardLine;
	for (int i = 0; i < line.length(); i++) // Puts the letters or '.' in a vector that represents a line of the board
		if (line[i] != ' ' && line[i] != '\n')
			boardLine.push_back(line[i]);
	
	numColumns = boardLine.size(); // Refreshes the number of lines and columns
	numLines++;

	return boardLine; // Returns a line of the board
}
