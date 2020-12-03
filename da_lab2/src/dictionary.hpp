#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <cctype> //std::tolower
#include <utility> //std::move

#include "avltree.hpp"

struct TDictionary : public TAVLTree<TString, uint64_t> {
	void Lowercase(TString &str) { //Метод, обеспечивающий регистронезависимость ключа
		int strSize = str.Size();
		for (int i = 0; i < strSize; i++) {
			str[i] = std::tolower(str[i]);
		}
	}

    void InputInsert() { //Метод для вставки слова в словарь
		TString key;
		uint64_t value = 0;

		std::cin >> key >> value;
		Lowercase(key);

		Add(std::move(key), value);
	}

    void InputRemove() { //Метод для удаления слова из словаря
		TString key;

		std::cin >> key;
		Lowercase(key);

		Delete(std::move(key));
	}

    void InputFind(const TString &k) { //Метод для нахождения слова в словаре
		TString key{k};

		Lowercase(key);

		TAVLNode *current = Find(std::move(key));
	}

    void InputSaveOrLoad() { //Метод для сохранения словаря в файл или его загрузки  
		TString input;
		TString fileName;

		std::cin >> input >> fileName;
		if (input[0] == 'S') {
			if (!OpenFileSave(fileName)) {
				std::cout << "ERROR: Couldn't create file" << std::endl;
				return;
			}
		}
		else {
			if (!OpenFileLoad(fileName)) {
				std::cout << "ERROR: Couldn't create file" << std::endl;
				return;
			}
		}
		std::cout << "OK" << std::endl;
	}

};

#endif //DICTIONARY_HPP