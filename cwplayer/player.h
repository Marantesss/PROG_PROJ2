#ifndef player_h
#define player_h

#include "board.h"
#include "dictionary.h"
#include <string>

class Player
{
public:
	Player();
	void playerOperations(Board &b, Dictionary dic);
	string boardToOpen();
	void showHints();
	void makeHints(Board b, Dictionary dic);
	void addHint(Board b, Dictionary dic, string position);
	void savePlayer(string crossFileName);
private:
	string nameOfPlayer;
	int timeElapsed;
	int aditionalHints;
	map<string, vector<string>> horizontalHints;
	map<string, vector<string>> verticalHints;
	string timeElapsed_min(int time);

};

#endif
