#include <iostream>
#include <vector>
#include <string>

using namespace std;
int main() {
	string input;
	while (!cin.eof()) {
		cout << "infix: ";
		cin >> input;
		cin.ignore(1000, '\n');
		cin.clear();
		cout << "postfix: " << input << endl;
	}
	return 0;
}

