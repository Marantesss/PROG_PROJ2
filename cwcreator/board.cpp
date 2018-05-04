#include "board.h"
#include <vector>
#include <iostream>
#include <utility>

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
	
	for (int i = 0; i < numColumns + 1; i++)
		cout << lowerLetters.at(i) << "  ";

	for (int i = 0; i < numLines; i++)
	{
		cout << endl;
		cout << upperLetters.at(i) << "  ";
		for (int j = 0; j < numColumns; j++)
			cout << board.at(i).at(j) << "  "; // 
	}
	cout << endl;
}

void Board::insertWord(string position, string word)
{
	int line, column;
	line = getIndex(toupper(position[0]));
	column = getIndex(toupper(position[1]));
	char orientation = toupper(position[2]);

	if (wordFitsSpace(line, column, orientation, word))
	{
		if (orientation == 'V' && wordMatchesSpace(line, column, orientation, word)) {
			if (line != 0)
				board.at(line - 1).at(column) = '#';
			for (int i = 0; i < word.length(); i++)
			{
				board.at(line).at(column) = toupper(word[i]);
				line++;
			};
			if (line < getLines() - 1)
				board.at(line).at(column) = '#';
		}

		if (orientation == 'H' && wordMatchesSpace(line, column, orientation, word)) {
			if (column != 0)
				board.at(line).at(column - 1) = '#';
			for (int i = 0; i < word.length(); i++)
			{
				board.at(line).at(column) = toupper(word[i]);
				column++;
			};
			if (column < getColumns() - 1)
				board.at(line).at(column) = '#';
		}

	}

}

int Board::getIndex(char letter)
{
	return (int)letter - 65;
}

bool Board::wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word)
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
{
	vector<pair<int, int>> temporaryNonRemovableLetters;
	int movingBoardVariable;
	if (orientation == 'V')  
	{
		movingBoardVariable = line;
		if (line != 0)
			if (board.at(movingBoardVariable - 1).at(column) != '.' && board.at(movingBoardVariable - 1).at(column) != '#')
				return false;

		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(movingBoardVariable).at(column) != '.')  // ADD  PALAVRAS (LETRAS/POSICOES QUE COINCIDEM) ()
			{
				if (board.at(movingBoardVariable).at(column) != word[i])
					return false;
				pair<int, int> dontRemove = make_pair(movingBoardVariable, column);
				temporaryNonRemovableLetters.push_back(dontRemove);
			}
			movingBoardVariable++;
		}
		nonRemovableLetters.insert(nonRemovableLetters.end(), temporaryNonRemovableLetters.begin(), temporaryNonRemovableLetters.end());
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
				if (board.at(line).at(movingBoardVariable) != word[i])
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
}

bool Board::isInNonRemovable(int line, int column)
{
	for (int i = 0; i < nonRemovableLetters.size(); i++)
		if (nonRemovableLetters.at(i).first == line && nonRemovableLetters.at(i).second == column)
		{
			nonRemovableLetters.erase(nonRemovableLetters.begin() + i);
			return true;
		}
	return false;
}