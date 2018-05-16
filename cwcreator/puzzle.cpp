#include "puzzle.h"
#include <iostream>

using namespace std;

/*
PROBLEMAS:
1 - Não dá para eliminar palavras escritas na vertical, mas na horizontal ja da
2 - (RESOLVIDO) Palavras validas que sao inseridas mas que nao cabem no board são na mesma adicionadas ao vetor position_word 
*/


Puzzle::Puzzle()
{
	int option = -1;

	cout << "CROSSWORD PUZZLE CREATOR" << endl;
	cout << "=======================================" << endl << endl;

	cout << "INSTRUCTIONS:" << endl;
	cout << "Input '?' anytime to get help" << endl; 
	cout << "Position (LCD / CTRL-Z = stop )" << endl;
	cout << "LCD stands for Line Column and Direction" << endl;
	//cout << "Mais instrucoes que nao sei..." << endl; 
	cout << endl; // TEMPORARIO
	cout << "---------------------------------------" << endl << endl;
	while (option != 0) {
		cout << "MENU" << endl << "1 - Create Puzzle" << endl << "2 - Resume Puzzle" << endl << "0 - Exit" << endl << endl;

		cout << "Option ? "; // opcao
		cin >> option;
		cin.clear(); // Limpa a errorFlag
		cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros
		if (option != 0 && option != 1 && option != 2)
			cout << "Not a valid option..." << endl << endl;

		if (option == 0 || option == 1 || option == 2) {
			switch (option) {
			case 1: createPuzzle();
				option = -1;
				break;
			case 2: resumePuzzle();
				option = -1;
				break;
			case 0: cout << "Closing Program..." << endl;
				break;
			}
		}
	}
}

int Puzzle::createPuzzle() {
	string dictionaryFile_name;
	ifstream dicFile;

	// DIRETORIO DO MARANTES: C:\\Users\\gonca\\Documents\\GitHub\\PROG_PROJ2\\synonyms_WINDOWS.txt
	//DIRETORIO DO TIAGO: C:\\Users\\tiago\\Desktop\\PROG_PROJ2\\synonyms_WINDOWS.txt

	cout << "---------------------------------------" << endl << "CREATE PUZZLE" << endl << "---------------------------------------" << endl;
	do {
		cout << "Dictionary file name ? ";
		cin >> dictionaryFile_name;

		dictionaryFileName = dictionaryFile_name; // VER SE E NECESSARIO

		dicFile.open(dictionaryFile_name); // Abre ficheiro de input

		if (!dicFile.is_open()) { // Se o ficheiro de input nao estiver aberto
			cout << "Couldn't open the file" << endl;
		}
	} while (!dicFile.is_open());
	dicFile.close();

	Dictionary dic(dictionaryFile_name); // Nao se pode passar um ifstream como argumento, tenho que passar o nome do ficheiro para ele abrir dentro da class

	int lin, col;
	do {
		cout << "Board size (lines columns) ? ";
		cin >> lin >> col;

		if (cin.fail()) { // Se o ficheiro de input nao estiver aberto
			cout << "Wrong input... Please insert two integers separated by space" << endl;
			cin.clear(); // Limpa a errorFlag
			cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros
		}
	} while (cin.fail());

	Board b(lin, col);

	cout << endl;
	b.showBoard();

	puzzleOperations(b, dic);

	return 0;
}

void Puzzle::puzzleOperations(Board b, Dictionary dic) {
	string position, word;
		
	while (true) {
		cout << endl << "Position ('LCD' / CTRL-Z = stop / ? = help)? ";
		cin >> position;
		if (position == "?") {  // Help input
			cout << "=== HELP ===" << endl;
			cout << "Enter coordinates and direction" << endl << "Example: CbH = Coordinates (C,b) horizontal" << endl;
			cout << endl << "Position ('LCD' / CTRL-Z = stop)? ";
			cin >> position;
		}
		if (cin.fail()) // Ends if entered CTRL+Z
			if (cin.eof()) {
				cin.clear();
				break;
			}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Word (? = help / - = remove word)? ";
		cin >> word;
		cin.clear();
		cin.ignore(1000, '\n');
		if (word == "?") {  // Help input
			cout << "=== HELP ===" << endl;
			cout << "Enter a word to be added to the crossword board (if its not in the dictionary you can try again)" << endl;
			cout << "Enter '-' to delete the word starting in the chosen position" << endl;
			cout << "Word? ";
			cin >> word;
		}
		if (word == "-") // Remove word input
			b.removeWord(position);
		if (dic.isValid(word) && !b.wordRepeated(word)) // Does the word belong in the dictionary?
			b.insertWord(position, word); // Insert word input
		else if (b.wordRepeated(word))
			cout << "Word was already inserted in the board" << endl;
		else if (word != "?" && word != "-") // Only shows error when word is different from 'help' and 'delete'
			cout << "Invalid word" << endl;
		b.showBoard();
		cout << endl;
	}

	int option;

	do {
		cout << endl << "OPTIONS" << endl;
		cout << "1- Save and resume later" << endl << "2- Finish" << endl;
		cin >> option;
		if (option != 1 && option != 2)   // Invalid entries 
			cout << "Not a valid option..." << endl << endl;

		if (option == 1) 
			b.saveBoard(dictionaryFileName);
		else if (option == 2) {
			b.finalizeBoard(); // Fills the elements that are not letters or '#' with '#'
			b.saveFinalBoard(dictionaryFileName);
		}
	} while (option != 1 && option != 2);

}

int Puzzle::resumePuzzle() { // Resume a criacao de um puzzle
	string dictionaryFile_name, crosswordsFile_name;
	ifstream dicFile;

	cout << "---------------------------------------" << endl << "RESUME PUZZLE" << endl << "---------------------------------------" << endl;

	cout << "Board file name ? ";
	cin >> crosswordsFile_name;

	crossFile.open(crosswordsFile_name);
	
	getline(crossFile, dictionaryFile_name); // Extracts the name of the dictionary file
	dictionaryFileName = dictionaryFile_name; // Puzzle class variable used to save the board

	Dictionary dic(dictionaryFile_name);
	Board b(0,0);

	b.loadBoard(crosswordsFile_name);
	b.showBoard();
	puzzleOperations(b, dic);

	crossFile.close();
	return 0;
}
