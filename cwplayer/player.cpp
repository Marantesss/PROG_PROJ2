#include "player.h"
#include "dictionary.h"
#include "board.h"
#include <string>
#include <fstream> 

using namespace std;

Player::Player()
{
	string dictionaryFile_name, crosswordsFile_name;
	ifstream dicFile, crossFile;

	crossFile.open(crosswordsFile_name);

	getline(crossFile, dictionaryFile_name);

	Dictionary dic(dictionaryFile_name);
	Board b(0, 0);
	Board bplayer(0, 0);

	b.loadBoard(crosswordsFile_name);
	bplayer.loadBoard(crosswordsFile_name);
	bplayer.emptyGrid();
	bplayer.showBoard();

}