#include "player.h"
#include "dictionary.h"
#include "board.h"
#include "colors.h"
#include <ctime>
#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
bool fileExists(const string fileName);

Player::Player()
{
	string dictionaryFile_name, crosswordsFile_name;
	ifstream dicFile, crossFile;

	cout << "---------------------------------------" << endl << "CROSSWORDS PLAYER" << endl << "---------------------------------------" << endl;
	cout << "=======================================" << endl << endl;

	cout << "INSTRUCTIONS:" << endl;
	cout << "Position (LCD / CTRL-Z = finish )" << endl;
	cout << "LCD stands for Line Column and Direction" << endl;
	cout << "=======================================" << endl << endl;



	string playerName;
	cout << "Name of Player? ";
	cin >> playerName;

	nameOfPlayer = playerName;

	crosswordsFile_name = boardToOpen(); // Randomizes a board that existes

	crossFile.open(crosswordsFile_name);

	getline(crossFile, dictionaryFile_name);

	Dictionary dic(dictionaryFile_name);
	Board bplayer(0, 0);

	cout << endl << "Opened board " << crosswordsFile_name << endl;
	
	bplayer.loadBoard(crosswordsFile_name);
	bplayer.emptyGrid();
	bplayer.showBoard();
	makeHints(bplayer, dic);
	showHints();

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	playerOperations(bplayer, dic);
	
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	timeElapsed = chrono::duration_cast<chrono::seconds>(end - begin).count();

	cout << "Checking solution..." << endl;

	if (bplayer.checkSolution()) 
	{
		setcolor(2);
		cout << "CONGRATS! Your solution is correct. " << endl;
		setcolor(7, 0);
		savePlayer(crosswordsFile_name);
	}
	else
	{
		cout << "Better luck next time...";
	}
}

string Player::boardToOpen() {
	ostringstream oss;
	vector<string> boardNames;

	for (int i = 1; i < 1000; i++) {
		oss << "b" << setfill('0') << setw(3) << i;
		oss << ".txt"; // oss = bxxx.txt

		if (fileExists(oss.str()))
			boardNames.push_back(oss.str());
		else {
			break;
		}
	}

	srand(time(NULL));

	int boardPos;
	boardPos = rand() % boardNames.size();

	return boardNames.at(boardPos);
}

void Player::playerOperations(Board &b, Dictionary dic)
{
	string position, word;

	while (true) {
		cout << endl << "Position ('LCD' / CTRL-Z = stop / ? = help)? ";
		cin >> position;
		if (position == "?") {  // Help input
			cout << "=== HELP ===" << endl;
			cout << "Enter coordinates and direction" << endl << "Example: CbH = Coordinates (C,b) horizontal" << endl;
			cout << endl << "Position ('LCD' / CTRL-Z = finish)? ";
			cin >> position;
			
		}
		if (cin.fail()) // Ends if entered CTRL+Z
			if (cin.eof()) {
				cin.clear();
				break;
			}

		while (!isValidPosition(b, position)) {
			cout << "Invalid position" << endl;
			cout << endl << "Position ('LCD' / CTRL-Z = stop / ? = help)? ";
			cin >> position;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Word (? = help / - = remove word)? ";
		cin >> word;
		cin.clear();
		cin.ignore(1000, '\n');
		
		if (word == "?") {  // Help input
			cout << "Hint will be added!" << endl;
			addHint(b, dic, position);                       // ERRO QUANDO NAO TEM MAIS HINTS E addiciona sempre que pede hints
			aditionalHints++;
			/*cout << "=== HELP ===" << endl;
			cout << "Enter a word to be added to the crossword board (if its not in the dictionary you can try again)" << endl;
			cout << "Enter '-' to delete the word starting in the chosen position" << endl;
			cout << "Word? ";
			cin >> word;*/
		}
		if (word == "-") // Remove word input
			b.removeWord(position);
		else if (dic.isValid(word)) // Does the word belong in the dictionary?
			b.insertWord(position, word); // Insert word input
		else if (word != "?" && word != "-") // Only shows error when word is different from 'help' and 'delete'
			cout << "Invalid word" << endl;
		b.showBoard();
		showHints();
		cout << endl;

		if (b.isBoardFull()) {
			char answer;
			cout << "The board is full, do you want to finish (Y/N)? ";
			cin >> answer;
			answer = toupper(answer);

			while (cin.fail() || (answer!='Y' && answer!='N')) { cin.clear(); cin.ignore(1000, '\n'); cout << "Invalid entry \n"; 
			cout << "The board is full, do you want to finish (Y/N)? ";
			cin >> answer;
			}
			if (answer == 'Y')
				break;
		}
	}
}

void Player::showHints() {
	cout << "HORIZONTAL" << endl;
	for (auto p : horizontalHints) {
		cout << p.first << "- ";
		for (int i = 0; i < p.second.size(); i++) {
			if (i == p.second.size() - 1)
				cout << p.second.at(i) << ";";
			else cout << p.second.at(i) << ", ";
		}
	}

	cout << "VERTICAL" << endl;
	for (auto p : verticalHints) {
		cout << p.first << "- ";
		for (int i = 0; i < p.second.size(); i++) {
			if (i == p.second.size() - 1)
				cout << p.second.at(i) << ";" << endl;
			else cout << p.second.at(i) << ", ";
		}
	}
}

void Player::makeHints(Board b, Dictionary dic) {
	
	for (auto p : b.getBoardWords())//int i = 0; i < b.getBoardWords().size(); i++)
	{
		string word = p.second;
		string position = p.first;
		vector<string> hints;
		hints.clear();

		if (position[2] == 'H') {
			position = position.substr(0, 2);
			dic.getHints(word, 2, hints);
			horizontalHints.insert(pair<string,vector<string>> (position, hints));
		}
		if (position[2] == 'V') {
			position = position.substr(0, 2);
			dic.getHints(word, 2, hints);
			verticalHints.insert(pair<string, vector<string>>(position, hints));
		}

	}
}

void Player::addHint(Board b, Dictionary dic, string position) { // Adds 1 hint to a specified position
	string word;
	map<string, vector<string>>::const_iterator index; 
	for (auto p: b.getBoardWords())/*int i = 0; i < b.getBoardWords().size(); i++)*/ { // Gets the word(answer) to find another synonym
		if (position == p.first)
			word = p.second;
	}
	vector<string> hints;
	if (position[2] == 'H') {
		position = position.substr(0, 2);
		index = horizontalHints.find(position);// Gets to the synonyms position
		for (int i = 0; i < index->second.size(); i++)
			hints.push_back(index->second.at(i));
		dic.getHints(word, 1, hints); // Adds a hint to the vector in the hints
		horizontalHints.erase(index);
		horizontalHints.insert(pair<string, vector<string>>(position, hints)); // Updates the map replacing the element
	}
	if (position[2] == 'V') {
		position = position.substr(0, 2);
		index = verticalHints.find(position);// Gets to the synonyms position
		for (int i = 0; i < index->second.size(); i++)
			hints.push_back(index->second.at(i));
		dic.getHints(word, 1, hints); // Adds a hint to the vector hints
		verticalHints.erase(index);
		verticalHints.insert(pair<string, vector<string>>(position, hints)); // Updates the map replacing the element
	}
}

void Player::savePlayer(string crossFileName)
{
	string recordsFileName = crossFileName.substr(0, 4) + "_t.txt";
	ofstream recordsFile;

	if (fileExists(recordsFileName))
	{
		recordsFile.open(recordsFileName, ios::app);
		recordsFile << endl << "Name of player: " << nameOfPlayer << "   Aditional hints: " << aditionalHints << "   Time elapsed: " << timeElapsed_min(timeElapsed) << endl;
	}
	else
	{
		recordsFile.open(recordsFileName);
		recordsFile << "======RECORDS - board " << crossFileName << "======" << endl << endl;
		recordsFile << "Name of player: " << nameOfPlayer << "   Aditional hints: " << aditionalHints << "   Time elapsed: " << timeElapsed_min(timeElapsed) << endl;
	}
}

string Player::timeElapsed_min(int time)
{
	int mins, secs;
	ostringstream timeElapsed_min;
	mins = time / 60;
	secs = time % 60;

	timeElapsed_min << mins << " minutes " << secs << " seconds";
	return timeElapsed_min.str();
}

bool fileExists(const string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}