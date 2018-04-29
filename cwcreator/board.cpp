#include "board.h"

Board::Board(int &columns, int &lines)
{
	this->columns = columns;
	this->lines = lines;
}

int Board::getColumns() const
{
	return columns;
}

int Board::getLines() const
{
	return lines;
}

void Board::showBoard()
{

}