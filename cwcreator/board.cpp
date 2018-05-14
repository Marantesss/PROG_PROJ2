#include "board.h"
#include "puzzle.h"
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>

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
	
	for (int i = 0; i < numColumns + 1; i++)  // Prints the upper line with the column identifiers
		cout << lowerLetters.at(i) << "  ";   // stored in the vector lowerletters

	for (int i = 0; i < numLines; i++)
	{
		cout << endl;
		cout << upperLetters.at(i) << "  ";  // Prints the identifier for each line
		for (int j = 0; j < numColumns; j++)
			cout << board.at(i).at(j) << "  "; // Prints each position of the board stored in board
	}
	cout << endl;
}

void Board::insertWord(string position, string word)
{
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Changes the word to uppercase

	if (wordFitsSpace(line, column, orientation, word))
	{
		if (orientation == 'V' && wordMatchesSpace(line, column, orientation, word)) { // insert VERTICAL words, if the word matches the space
			if (line != 0)
				board.at(line - 1).at(column) = '#'; // If the word is not being inserted in the beginning of a column places a '#' in the position before
			for (int i = 0; i < word.length(); i++)
			{
				board.at(line).at(column) = word[i]; // inserts the word by changing the vector board
				line++;
			};
			if (line < getLines() - 1) 
				board.at(line).at(column) = '#'; // If the word does not end in the last position of a column places a '#' in the next position
		}

		if (orientation == 'H' && wordMatchesSpace(line, column, orientation, word)) { // insert HORIZONTAL words, if the word matches the space
			if (column != 0)
				board.at(line).at(column - 1) = '#'; // If the word is not being inserted in the beginning of a  places a '#' in the position before
			for (int i = 0; i < word.length(); i++)
			{
				board.at(line).at(column) = word[i]; // inserts the word by changing the vector board
				column++;
			};
			if (column < getColumns() - 1)
				board.at(line).at(column) = '#'; // If the word does not end in the last position of a line places a '#' in the next position
		}
		if (!wordMatchesSpace(line, column, orientation, word)) 
			cerr << "The word does not match the space" << endl; // displays error message if the word does not match the space

	}
	else
		cerr << "The word does not fit the space" << endl; // displays error message if the word does not fit the space

	position_words.push_back(make_pair(position, word)); // Adds a pair of (position - word) to a vector
}

int Board::getIndex(char letter) // Gets the index of a given letter of line or column 
{
	return (int)letter - 65;
}

bool Board::wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word) 
// Checks if the word fits the column/line starting from the user entered position
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
// Cheks if the word matches with the already in-board letters
{
	vector<pair<int, int>> temporaryNonRemovableLetters;
	int movingBoardVariable;
	if (orientation == 'V')  
	{
		movingBoardVariable = line;
		if (line != 0)
			if (board.at(movingBoardVariable - 1).at(column) != '.' && board.at(movingBoardVariable - 1).at(column) != '#') 
				return false; // If the char before is not '.' or '#' returns false

		// verificaçao da letra seguinte

		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(movingBoardVariable).at(column) != '.')  
			{
				if (board.at(movingBoardVariable).at(column) != toupper(word[i])) // If the word letter is different from the board letter returns false
					return false;
				pair<int, int> dontRemove = make_pair(movingBoardVariable, column); // Crossover letters
				temporaryNonRemovableLetters.push_back(dontRemove);
			}
			movingBoardVariable++;
		}
		nonRemovableLetters.insert(nonRemovableLetters.end(), temporaryNonRemovableLetters.begin(), temporaryNonRemovableLetters.end()); // If the path leaves the loop adds the crossover letters to a vector
		return true;
	}
	
	if (orientation == 'H')
	{
		movingBoardVariable = column;
		if (column != 0)
			if (board.at(line).at(movingBoardVariable - 1) != '.' && board.at(line).at(movingBoardVariable - 1) != '#')
				return false;

		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(line).at(movingBoardVariable) != '.')
			{
				if (board.at(line).at(movingBoardVariable) != toupper (word[i]))
					return false;
				pair<int, int> dontRemove = make_pair(line, movingBoardVariable);
				temporaryNonRemovableLetters.push_back(dontRemove);
			}
			movingBoardVariable++;
		}
		nonRemovableLetters.insert(nonRemovableLetters.end(), temporaryNonRemovableLetters.begin(), temporaryNonRemovableLetters.end());
		return true;
	}
}


void Board::removeWord(string position)
{
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);

	if (orientation == 'V')
	{
		if (line != 0)
			board.at(line - 1).at(column) = '.';
		
		while (board.at(line).at(column) != '#' && line < getLines())
		{
			if (!isInNonRemovable(line, column)) // isNonRemovable gets line and column;
				board.at(line).at(column) = '.';
			line++;
		}
		if (line < getLines())
			board.at(line).at(column) = '.';
	}

	if (orientation == 'H')
	{
		if (column != 0)
			board.at(line).at(column-1) = '.';

		while (board.at(line).at(column) != '#' && column < getColumns())
		{
			if (!isInNonRemovable(line, column)) // isNonRemovable gets line and column;
				board.at(line).at(column) = '.';
			column++;
		}
		if (column < getColumns())
			board.at(line).at(column) = '.';
	}
	for (int i = 0; i < position_words.size(); i++) // Removes the position and the word from the vector 
		if (position_words.at(i).first == position)
			position_words.erase(position_words.begin() + i);
}

bool Board::isInNonRemovable(int line, int column)
{
	for (int i = 0; i < nonRemovableLetters.size(); i++) // Checks if the pair is in the nonRemovableLetters 
		if (nonRemovableLetters.at(i).first == line && nonRemovableLetters.at(i).second == column)
		{
			nonRemovableLetters.erase(nonRemovableLetters.begin() + i); // If so removes that pair 
			return true;
		}
	return false;
}

void Board::finalizeBoard()
{
	for (int i = 0; i < getLines(); i++) // Fills the elements that are not letters or '#' with '#'
		for (int j = 0; j < getColumns(); j++)
			if (board.at(i).at(j) == '.')
				board.at(i).at(j) = '#';

}

void Board::saveBoard(string dictionaryFileName)
{
	ofstream boardFile;
	
	cout << "File will be saved into a text file (enter only the name of the file)  ";
	string fileName;
	cin >> fileName;

	fileName += ".txt"; 
	boardFile.open(fileName);
	
	boardFile << dictionaryFileName << endl;

	for (int i = 0; i < numLines; i++)
	{
		boardFile << endl;
		for (int j = 0; j < numColumns; j++)
			boardFile << board.at(i).at(j) << "  ";
	}

	boardFile << endl;

	for (int i = 0; i < position_words.size(); i++)
	{
		boardFile << endl;
		boardFile << position_words.at(i).first << " " << position_words.at(i).second;
	}
}
void Board::saveFinalBoard(string dictionaryFileName)
{
	ofstream boardFile;

	string fileName;
	cin >> fileName;

	fileName += ".txt";
	boardFile.open(fileName);

	boardFile << dictionaryFileName << endl;

	for (int i = 0; i < numLines; i++)
	{
		boardFile << endl;
		for (int j = 0; j < numColumns; j++)
			boardFile << board.at(i).at(j) << "  ";
	}

	boardFile << endl;

	for (int i = 0; i < position_words.size(); i++)
	{
		boardFile << endl;
		boardFile << position_words.at(i).first << " " << position_words.at(i).second;
	}
}


void Board::loadBoard(string fileName)
{
	ifstream boardFile;
	string line;

	boardFile.open(fileName);
	
	if (!boardFile.is_open())
		cout << "Couldn't open the file";

	getline(boardFile, line);
	boardFile.seekg(line.length() + 4); // moves the pointer to the line containing
	
	getline(boardFile, line);

	while (!boardFile.eof())
	{
		board.push_back(loadBoardLine(line));
		getline(boardFile, line);
		if (line == "\n" || line == "")
			break;
	}
	
	while (!boardFile.eof())
	{
		string position, word;
		getline(boardFile, line);
		
		position = line.substr(0, 3);
		word = line.substr(4);

		position_words.push_back(make_pair(position, word));
	}


}

vector<char> Board::loadBoardLine(string &line)
{
	vector<char> boardLine;
	for (int i = 0; i < line.length(); i++)
		if (line[i] != ' ' && line[i] != '\n')
			boardLine.push_back(line[i]);
	
	numColumns = boardLine.size();
	numLines++;

	return boardLine;
}