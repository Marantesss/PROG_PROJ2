#include "dictionary.h"

Dictionary::Dictionary(ifstream file)
{
	string s; // String onde vai ser guardado uma linha do ficheiro de sinonimos

	for (int i = 0; !file.eof(); i++)
	{
		getline(file, s);
		if(!s.empty()) // Se s nao for uma string vazia aloca as palavras de s no vetor
			synonymes[i] = extractWords(s);
	}
}

vector<string> Dictionary::extractWords(string line) // Separa as palavras separadas por ", "  e retorna um membro do vetor synonymes
{
	vector<string> words;
	int pos = 0; //posicao do primeiro char de cada word na string
	int index = 0;
	string word;

	// Aloca a palavra que vai ter sinonimos
	index = line.find_first_of(':', pos);
	word = line.substr(pos, index); // substring entre o pos e o index
	pos = pos + index + 2; // pos fica com o numero da posicao do primeiro char do priemiro sinonimo na line
	words.push_back(word);
	line = line.substr(pos);  // elimina da line o que já foi alocado no vetor
	pos = 0;

	// Aloca os sinonimos todos depois da palavra
	while (!line.empty())
	{
		index = line.find_first_of(',', pos);
		if (index != -1) // CASO NAO TENHA NENHUM "," find_first_of devolve -1, então a linha só tem mais um sinonimo
		{
			word = line.substr(pos, index); // substring entre o pos e o index
			pos = pos + index + 2; // pos fica com o numero da posicao do primeiro char do proximo sinonimo na line
			words.push_back(word);
			line = line.substr(pos);  // elimina da line o que já foi alocado no vetor
			pos = 0;
		}
		else
		{
			words.push_back(line);
		}
	}

	return words;
}