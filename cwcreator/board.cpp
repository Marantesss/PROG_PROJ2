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