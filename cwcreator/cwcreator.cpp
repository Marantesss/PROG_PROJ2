#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include "board.h"
#include "dictionary.h"
#include "puzzle.h"
#include "colors.h"

using namespace std;

bool wildcardMatch(const char *str, const char *strWild) { // Funcao simple wildcard do Anexo C
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

int main() {
	Puzzle p;

	return 0;
}