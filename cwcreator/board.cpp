#include "board.h"
#include <vector>
#include <iostream>

Board::Board(int columns, int lines)
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
			cout << board.at(i).at(j) << "  ";
	}

}

void Board::insertWord(string position, string word)
{
	int line, column;
	line = getNumber(position[0]);
	column = getNumber(position[1]);
	char orientation = position[2];

	if (wordFitsSpace(line, column, orientation, word))
	{
		if (toupper(orientation) == 'V' && wordMatchesSpace(line, column, orientation, word))
			for (int i = 0; i < word.length(); i++)
			{
				board.at(line).at(column) = word[i];
				line++;
			};
		
		if (toupper(orientation) == 'H' && wordMatchesSpace(line, column, orientation, word))
			for (int i = 0; i < word.length(); i++)
			{
				board.at(line).at(column) = word[i];
				column++;
			};
	}

}

int Board::getNumber(char letter)
{
	toupper(letter);

	return (int)letter - 65;
}

bool Board::wordFitsSpace(int const &line, int const &column, char const &orientation, string const &word)
{
	if (toupper(orientation) == 'V')
	{
		if (getLines() - line >= word.length())
			return true;
		else return false;
	}
	if (toupper(orientation) == 'H')
	{
		if (getColumns() - column >= word.length())
			return true;
		else return false;
	}	
}

bool Board::wordMatchesSpace(int const &line, int const &column, char const &orientation, string const &word)
{
	
	int movingBoardVariable; 

	if (toupper(orientation) == 'V')
	{
		movingBoardVariable = line;
		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(movingBoardVariable).at(column) != '.')  // ADICIONAR CODIGO PARA REMOVER PALAVRAS (LETRAS/POSICOES QUE COINCIDEM)
				if (board.at(movingBoardVariable).at(column) != word[i])
					return false;
			movingBoardVariable++;
		}
		return true;
	}
	
	if (toupper(orientation) == 'H')
	{
		movingBoardVariable = column;
		for (int i = 0; i < word.length(); i++)
		{
			if (board.at(line).at(movingBoardVariable) != '.')
				if (board.at(line).at(movingBoardVariable) != word[i])
					return false;
			movingBoardVariable++;
		}
		return true;
	}
	

}
