#ifndef player_h
#define player_h

#include "board.h"
#include "dictionary.h"
#include <string>

class Player
{
public:
	Player();
	void playerOperations(Board b, Dictionary dic);
	void showHints();
	void makeHints(Board b, Dictionary dic);
private:
	string nameOfPlayer;
	int time;
	map<string, vector<string>> horizontalHints;
	map<string, vector<string>> verticalHints;
};

#endif
