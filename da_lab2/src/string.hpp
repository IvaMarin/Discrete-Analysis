#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <algorithm>
#include <utility>

const int COEFF = 2; //Коэффициент динамического раширения строки

struct TString { //Строковая структура
	using valueType = char;
	using iterator = valueType *;
	using constIterator = const valueType *;

	TString() : storageSize{0}, alreadyUsed{0}, storage{nullptr} {}; //Конструктор по умолчанию

	TString(const valueType *str) { //Конструктор
		alreadyUsed = std::strlen(str);
		storageSize = alreadyUsed + 1;
		storage = new valueType[storageSize];
		std::copy(str, str + alreadyUsed, storage);
		storage[alreadyUsed] = '\0';
	}

	TString(const TString &str) {
		storageSize = str.storageSize;
		alreadyUsed = str.alreadyUsed;
		storage = new valueType[storageSize];
		std::copy(str.storage, str.storage + alreadyUsed, storage);
		storage[alreadyUsed] = '\0';
	}

	TString(TString &&str) {
		alreadyUsed = str.alreadyUsed;
		storageSize = str.storageSize;
		storage = str.storage;
		str.storage = nullptr;
	}

	TString &operator=(const valueType *str) { //Перегрузка оператора копирования
		delete [] storage;
		alreadyUsed = std::strlen(str);
		storageSize = alreadyUsed + 1;
		storage = new valueType[storageSize];
		std::copy(str, str + alreadyUsed, storage);
		storage[alreadyUsed] = '\0';
		return *this;
	}

	TString &operator=(const TString &str) {
		valueType *temp = new valueType[str.storageSize];
		std::copy(str.storage, str.storage + str.storageSize, temp);
		delete [] storage;
		storage = temp;
		temp = nullptr;
		alreadyUsed = str.alreadyUsed;
		storageSize = str.storageSize;
		return *this;
	}

	TString &operator=(TString &&str) {
		delete [] storage;
		alreadyUsed = str.alreadyUsed;
		storageSize = str.storageSize;
		storage = str.storage;
		str.storage = nullptr;
		return *this;
	}

	void CstrMove(valueType *str) { //Метод Move для данной строки
		delete [] storage;
		storage = str;
		alreadyUsed = strlen(str);
		storageSize = alreadyUsed + 1;
		str = nullptr;
	}

	void Swap(TString &str) { //Обмен данными между строками
		std::swap(alreadyUsed, str.alreadyUsed);
		std::swap(storageSize, str.storageSize);
		std::swap(storage, str.storage);
	}

	void PushBack(const valueType &ch) { //Метод для добавления символа в  строку
		if (alreadyUsed + 1 == storageSize) {
			int newStorageSize = storageSize ? storageSize * COEFF : 1;
			valueType *newStorage = new valueType[newStorageSize];
			std::copy(storage, storage + storageSize, newStorage);
			delete [] storage;
			storage = newStorage;
			storageSize = newStorageSize;
		}

		storage[alreadyUsed] = ch;
		alreadyUsed++;
		storage[alreadyUsed] = '\0';
	}

	~TString() { //Деструктор
		delete [] storage;
		storageSize = 0;
		alreadyUsed = 0;
		storage = nullptr;
	}

	iterator begin() { //Начало итерирования по строке
		return storage;
	}

	constIterator begin() const {
		return storage;
	}

	iterator end() { //Завершение итерирования по строке
		if (storage != nullptr) {
			return storage + alreadyUsed;
		}
		return nullptr;
	}

	constIterator end() const {
		if (storage != nullptr) {
			return storage + alreadyUsed;
		}
		return nullptr;
	}

	const valueType *Cstr() const { //Метод для нахождения размера строки
		return storage;
	}

	int Size() const {
		return alreadyUsed;
	}

	TString &operator+=(const valueType &ch) { //Перегрузка оператора +=
		PushBack(ch);
		return *this;
	}

	const valueType &At(int index) const { //Получение символа в строке
		if (index < 0 || index > alreadyUsed) {
			throw std::out_of_range("You are doing this wrong!");
		}

		return storage[index];
	}

	valueType &At(int index) {
		const valueType &elem = const_cast<const TString *>(this)->At(index);
		return const_cast<valueType &>(elem);
	}

	const valueType &operator[](int index) const { //Перегрузка оператора []
		return At(index);
	}

	valueType &operator[](int index) {
		return At(index);
	}

	friend std::ostream &operator<<(std::ostream &os, const TString &str); //Перегрузка оператора вывода
	friend std::istream &operator>>(std::istream &is, TString &str); //Перегрузка оператора ввода

private:
	int storageSize; //Размер хранилища
	int alreadyUsed;
	valueType *storage; //Хранилище
};

std::ostream &operator<<(std::ostream &os, const TString &str) {
	for (auto ch : str) {
		os << ch;
	}
	return os;
}

std::istream &operator>>(std::istream &is, TString &str) {
	char buf[300];
	if (is >> buf) {
		str = buf;
	}
	return is;
}

bool operator<(const TString &lhs, const TString &rhs) { //Перегрузка оператора <
	int minSize = std::min(lhs.Size(), rhs.Size());
	for (int i = 0; i < minSize; i++) {
		if (lhs[i] != rhs[i]) {
			return lhs[i] < rhs[i];
		}
	}
	return lhs.Size() < rhs.Size();
}

bool operator>(const TString &lhs, const TString &rhs) { //Перегрузка оператора >
	return rhs < lhs;
}

bool operator==(const TString &lhs, const TString &rhs) { //Перегрузка оператора ==
	return !(lhs > rhs) && !(lhs < rhs);
}

bool operator!=(const TString &lhs, const TString &rhs) { //Перегрузка оператора !=
	return !(lhs == rhs);
}

#endif // STRING_HPP