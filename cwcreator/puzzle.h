#ifndef puzzle_h
#define puzzle_h

#include "dictionary.h"
#include "board.h"
#include <string>

using namespace std;

class Puzzle
{
public:
	Puzzle();
	int createPuzzle();
	void puzzleOperations(Board b, Dictionary dic);
	int resumePuzzle();
private:
	string dictionaryFileName;
	ifstream crossFile; // File opened to resume puzzle creation
};

#endif
