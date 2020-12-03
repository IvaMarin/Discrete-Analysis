#include <iostream>
#include <fstream>
#include <utility> //std::move

#include "dictionary.hpp"

int main() {

	std::ios::sync_with_stdio(false); //Отключение синхронизации iostreams с stdio
	std::cin.tie(nullptr); //Отключение привязки cin к cout

	TString input;
	TDictionary dictionary;

	while (std::cin >> input) {
		if (input[0] == '+') {
			dictionary.InputInsert();
		}
		else if(input[0] == '-') {
			dictionary.InputRemove();
		}
		else if(input[0] == '!' && input.Size() == 1) {
			dictionary.InputSaveOrLoad();
		}
		else {
			dictionary.InputFind(std::move(input));
		}
	}

	return 0;
}
