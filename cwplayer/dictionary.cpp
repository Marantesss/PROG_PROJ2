#include "dictionary.h"
#include "colors.h"
#include <iostream>
#include <algorithm> // Transform
#include <time.h>
#include <stdlib.h>

Dictionary::Dictionary(string fileName) {
	string s; // String onde vai ser guardado uma linha do ficheiro de sinonimos
	ifstream file;

	file.open(fileName); // Abre o ficheiro

	while(!file.eof()) {
		getline(file, s);
		if (!s.empty()) { // Se s nao for uma string vazia aloca as palavras de s no vetor
			vector<string> aux = extractWords(s);
			vector<string> aux2(aux.begin() + 1, aux.end());
			synonymes.insert(pair<string, vector<string>>(aux[0], aux2));
		}
	}
}

vector<string> Dictionary::extractWords(string line) { // Separa as palavras separadas por ", "  e retorna um membro do vetor synonymes
	vector<string> words;
	int pos = 0; //posicao do primeiro char de cada word na string
	int index = 0;
	string word;

	// Aloca a palavra que vai ter sinonimos
	index = line.find_first_of(':', pos);
	word = line.substr(pos, index); // substring entre o pos e o index
	pos = pos + index + 2; // pos fica com o numero da posicao do primeiro char do priemiro sinonimo na line
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma em maisculas
	words.push_back(word);
	line = line.substr(pos);  // elimina da line o que já foi alocado no vetor
	pos = 0;

	// PROBLEMA DE MERDA DA LINHA 29 DO DICIONARIO
	if (',' == line[line.size() - 1]) { // Se a ultima virgula for no final da string
		line = line.substr(0, line.size() - 1);
	}

	// Aloca os sinonimos todos depois da palavra
	while (!line.empty()) {
		index = line.find_first_of(',');
		if (index != -1) { // CASO NAO TENHA NENHUM "," find_first_of devolve -1, então a linha só tem mais um sinonimo
			word = line.substr(pos, index); // substring entre o pos e o index
			pos = pos + index + 2; // pos fica com o numero da posicao do primeiro char do proximo sinonimo na line
			transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma em maisculas
			words.push_back(word);
			line = line.substr(pos);  // elimina da line o que já foi alocado no vetor
			pos = 0;
		}
		else {
			transform(line.begin(), line.end(), line.begin(), ::toupper);
			words.push_back(line);
			line = line.substr(line.size());
		}
	}
	return words;
}

bool Dictionary::isValid(string word) { // Verifica se uma palavra pertence ao dicionario
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma a word em maiscula

	if (synonymes.find(word) != synonymes.end()) // Se a posicao da word no map for o final do map, a word nao existe em map
		return true;
	else
		return false;
	/*
	for (int i = 0; i <= synonymes.size(); i++)
	{
		if (i == synonymes.size()) // Acabou o vetor
			return false;
		else if (word == synonymes[i][0]) // Se a word for igual a primeira palavra de cada vetor
			return true;
	}
	*/
}

vector<string> Dictionary::wildcard(string pseudoWord) { // Recebe parte de uma palavra e devolve um vetor com todas as palavras que podem ser escritas
	vector<string> matchingWords;

	for (auto p : synonymes) { // p.first = KEY e p.second = VALUE
		if (wildcardMatch(p.first.c_str(), pseudoWord.c_str()))
			matchingWords.push_back(p.first);
	}

	return matchingWords;
}

bool Dictionary::wildcardMatch(const char *str, const char *strWild) { // Funcao simple wildcard do Anexo C
	while (*strWild) {
		if (*strWild == '?') {
			if (!*str)
				return false;
			++str;
			++strWild;
		}
		else if (*strWild == '*') {
			if (wildcardMatch(str, strWild + 1))
				return true;
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			return false;
		}
		else {
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	return !*str && !*strWild;
}

void Dictionary::getHints(string word, int numHints, vector<string> &hints) {  // Vector as parameter so it can add hints to a non-empty vector
	map<string, vector<string>>::const_iterator index = synonymes.find(word);
	srand(time(NULL));

	for (int i = 1; i <= numHints; i++) { // Loop for the number of hints
		bool isInHints;
		do {
			int randPos = rand() % (index->second.size()); // Random number [0, (number of synonyms -1)]
			isInHints = false;

			if (hints.size() == 0)
				hints.push_back(index->second.at(randPos)); // If the vector of hints is empty then adds a random synonym

			else { // If the vector is NOT empty checks if the synonym is already in the hints vector
				for (int j = 0; j < hints.size(); j++)
					if (index->second.at(randPos) == hints.at(j))
						isInHints = true;
				if (!isInHints) // If not adds the synonym to the vector
					hints.push_back(index->second.at(randPos));
			}
			if (index->second.size() == hints.size()) {
				setcolor(14);
				std::cout << "No more hints available!" << endl;
				setcolor(7, 0);
				break;
			}
		} while (isInHints);
	}
}