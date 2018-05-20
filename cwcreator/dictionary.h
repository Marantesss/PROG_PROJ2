#ifndef dictionary_h
#define dictionary_h
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class Dictionary {
public:
	Dictionary(string fileName); // Recebe o ficheiro e separa as palavras e sinonimos
	bool isValid(string word); // Verifica se uma palavra pertence ao dicionario
	vector<string> wildcard(string pseudoWord); // Recebe parte de uma palavra e ve quais pode escrever com essa
private:
	// Funcoes
	vector<string> extractWords(string line); // Retrieves words separated by ", "  and returns a member 
	bool wildcardMatch(const char *str, const char *strWild); // Funcao simple wildcard do Anexo C
	// Variaveis
	map<string, vector<string>> synonymes;	// Map where KEY is the word, and VALUE is the synonymes
};

#endif
