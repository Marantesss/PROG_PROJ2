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
	void getHints(string word, int numHints, vector<string> &hints);
private:
	// Funcoes
	vector<string> extractWords(string line); // Separa as palavras separadas por ", "  e retorna um membro do vetor synonymes
	bool wildcardMatch(const char *str, const char *strWild); // Funcao simple wildcard do Anexo C
	// Variaveis
	map<string, vector<string>> synonymes;	// Map onde vai ser guardado as linhas do ficheiro synonyms (palavra, sinonimo, sinonimo, sinonimo)
};

#endif
