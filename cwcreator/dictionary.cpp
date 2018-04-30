#include "dictionary.h"
#include <algorithm> // Transform

Dictionary::Dictionary(ifstream file)
{
	string s; // String onde vai ser guardado uma linha do ficheiro de sinonimos

	while(!file.eof())
	{
		getline(file, s);
		if (!s.empty()) // Se s nao for uma string vazia aloca as palavras de s no vetor
		{
			vector<string> aux = extractWords(s);
			vector<string> aux2(aux.begin() + 1, aux.end());
			synonymes.insert(pair<string, vector<string>>(aux[0], aux2));
		}
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
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma em maisculas
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
			transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma em maisculas
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

bool Dictionary::isValid(string word) // Verifica se uma palavra pertence ao dicionario
{
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma a word em maiscula

	if (synonymes[word].empty) // Se o map devolver um vetor vazio, a palavra nao existe
		return false;
	else
		return true;
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

vector<string> Dictionary::wildcard(string pseudoWord) // Recebe parte de uma palavra e devolve um vetor com todas as palavras que podem ser escritas
{
	vector<string> matchingWords;

	for (int i = 0; synonymes.size(); i++)
	{
		if (wildcardMatch(/*WORD*/.c_str(), pseudoWord.c_str()))
		{
			matchingWords.push_back(/*WORD*/);
		}
	}
	return matchingWords;
}

bool Dictionary::wildcardMatch(const char *str, const char *strWild) // Funcao simple wildcard do Anexo C
{
	while (*strWild)
	{
		if (*strWild == '?')
		{
			if (!*str)
				return false;
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			if (wildcardMatch(str, strWild + 1))
				return true;
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			return false;
		}
		else
		{
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	return !*str && !*strWild;
}
