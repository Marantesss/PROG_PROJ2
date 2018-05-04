#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "board.h"
#include "dictionary.h"

using namespace std;

int createPuzzle(); // Cria Puzzle
int resumePuzzle(); // Resume a criacao de um puzzle

int main() {
	int option = -1;

	cout << "CROSSWORD PUZZLE CREATOR" << endl;
	cout << "=======================================" << endl << endl;

	cout << "INSTRUCTIONS:" << endl;
	//cout << "Mais instrucoes que nao sei..." << endl; 
	cout << "Position (LCD / CTRL-Z = stop )" << endl;
	cout << "LCD stands for Line Column and Direction" << endl;
	//cout << "Mais instrucoes que nao sei..." << endl; 
	cout << endl; // TEMPORARIO
	cout << "---------------------------------------" << endl << endl;
	while (option != 0) {
		cout << "OPTIONS" << endl << "1 - Create Puzzle" << endl << "2 - Resume Puzzle" << endl << "0 - Exit" << endl << endl;

		cout << "Option ? "; // opcao
		cin >> option;
		cin.clear(); // Limpa o buffer
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

	return 0;
}

int createPuzzle() { // Cria Puzzle
	string dictionaryFile_name;
	ifstream dicFile;

	// DIRETORIO DO MARANTES: C:\\Users\\gonca\\Documents\\GitHub\\PROG_PROJ2\\synonyms_WINDOWS.txt
	//DIRETORIO DO TIAGO: C:\\Users\\tiago\\Desktop\\PROG_PROJ2\\synonyms_WINDOWS.txt

	cout << "---------------------------------------" << endl << "CREATE PUZZLE" << endl << "---------------------------------------" << endl;
	do {
		cout << "Dictionary file name ? ";
		cin >> dictionaryFile_name;

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
			cout << "Couldn't open the file" << endl;
		}
	} while (cin.fail());

	Board b(lin, col);

	cout << endl;
	b.showBoard();

	string position, word;

	while(true) {
		cout << endl << "Position ('LCD' / CTRL-Z = stop)? ";
		cin >> position;
		if (cin.eof()) // Acaba o ciclo se fizer CTRL+Z
			break;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Word? ";
		cin >> word;

		b.insertWord(position, word);
		b.showBoard();
		cout << endl;
	}

	return 0;
}


int resumePuzzle() { // Resume a criacao de um puzzle
	string dictionaryFile_name, crosswordsFile_name;
	ifstream dicFile, crossFile;

	return 0;
}