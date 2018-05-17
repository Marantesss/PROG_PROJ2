#include "player.h"
#include "dictionary.h"
#include "board.h"
#include "colors.h"
#include <string>
#include <iostream>
#include <fstream> 

using namespace std;

Player::Player()
{
	string dictionaryFile_name= "synonyms.txt", crosswordsFile_name="tryout.txt";
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

	crossFile.open(crosswordsFile_name);

	getline(crossFile, dictionaryFile_name);

	Dictionary dic(dictionaryFile_name);
	Board b(0, 0);
	Board bplayer(0, 0);

	b.loadBoard(crosswordsFile_name);
	bplayer.loadBoard(crosswordsFile_name);
	bplayer.emptyGrid();
	bplayer.showBoard();
	makeHints(bplayer, dic);
	showHints();

	playerOperations(bplayer, dic);


}

void Player::playerOperations(Board b, Dictionary dic)
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
			cout << "Hint will be added" << endl;
			addHint(b, dic, position);
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
	
	for (int i = 0; i < b.getBoardWords().size(); i++) 
	{
		string word = b.getBoardWords().at(i).second;
		string position = b.getBoardWords().at(i).first;
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
	for (int i = 0; i < b.getBoardWords().size(); i++) { // Gets the word(answer) to find another synonym
		if (position == b.getBoardWords().at(i).first)
			word = b.getBoardWords().at(i).second;
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