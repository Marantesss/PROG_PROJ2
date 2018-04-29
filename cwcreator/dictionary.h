#ifndef dictionary_h
#define dictionary_h
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Dictionary {
public:
	Dictionary(ifstream file); // Recebe o ficheiro e separa as palavras e sinonimos
private:
	vector<string> extractWords(string line); // Separa as palavras separadas por ", "  e retorna um membro do vetor synonymes
	vector<vector<string>> synonymes; //Vector onde vai ser guardado as linhas do ficheiro synonyms (palavra, sinonimo, sinonimo, sinonimo)
};

#endif
