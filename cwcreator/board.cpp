#include "board.h"
#include <vector>
#include <iostream>

Board::Board(int columns, int lines)
{
	numColumns = columns;
	numLines = lines;
	
	board.resize(numLines);
	for (int i = 0; i < numLines; i++)
		board[i].resize(numColumns);


	for (int i = 0; i < numLines; i++)
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
	for (int i = 0; i < numLines; i++)
	{
		for (int j = 0; j < numColumns; j++)
			cout << board.at(i).at(j) << " ";
		cout << endl;
	}

}