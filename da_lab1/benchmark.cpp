#include <iostream>
#include <chrono>
#include <cassert> // для функции assert
#include <algorithm>


using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

/*
using duration_t = std::chrono::milliseconds;
const std::string DURATION_PREFIX = "ms";
*/

const int SIZE = 65; //Длина значения

struct TPair {
	unsigned short key; //Ключ: числа от 0 до 65535.
	char value[SIZE]; //Значение: строки фиксированной длины 64 символа
	TPair(); //Конструктор по умолчанию
	TPair(int i, char *str); //Конструктор
	void Fill(char ch = '\0'); //Метод для заполнения значения нулями
}; //Пара «ключ-значение»

TPair::TPair() {
	key = 0;
	Fill();
} //Реализация конструктора по умолчанию

TPair::TPair(int i, char *str) {
	key = i;
	Fill();
	for (register unsigned int i = 0; i < sizeof(str) / sizeof(char); i++) {
		value[i] = str[i];
	}
} //Реализация конструктора

void TPair::Fill(char ch) {
	for (register unsigned int i = 0; i < sizeof(value) / sizeof(char); i++) {
		value[i] = ch;
	}
} //Реализация метода для заполнения значения нулями



template <typename T> 
class TVector {
public:
	using TValueType = T;
	using TIterator = TValueType *;
	TVector(); //Конструктор по умолчанию
	TVector(unsigned int size); //Конструктор
	unsigned int Size() const; //Метод вывода размера вектора
	bool Empty() const; //Проверка на пустоту вектора
	TIterator Begin() const; //Установка итератора
	TIterator End() const; //Снятие итератора

	template <typename U> 
    friend void Swap(TVector<U> &first, TVector<U> &second); //Метод обмена значениями

	TVector &operator=(TVector other); //Перегрузка оператора =
	~TVector(); //Деструктор
	TValueType &operator[](int index) const; //Перегрузка оператора []
	void PushBack(TValueType &value); //Метод ввода значений в вектор

	template <typename U> 
    friend TVector<U> CountingSort(const TVector<U> &unsortedVector, unsigned int max); //Сортировка подсчетом

private:
	int storageSize;
	int alreadyUsed;
	TValueType *storage;
}; //Класс вектор

template <typename T> 
TVector<T>::TVector() {
	storageSize = alreadyUsed = 0;
	storage = nullptr;
}

template <typename T> 
TVector<T>::TVector(unsigned int size) : TVector() {
	assert(size >= 0);

	if (size == 0) {
		return;
	}
	storageSize = alreadyUsed = size;
	storage = new typename TVector<T>::TValueType[size];
}

template <typename T> 
unsigned int TVector<T>::Size() const {
	return alreadyUsed;
}

template <typename T> 
bool TVector<T>::Empty() const {
	return Size() == 0;
}

template <typename T> typename 
TVector<T>::TIterator TVector<T>::Begin() const {
	return storage;
}

template <typename T> typename 
TVector<T>::TIterator TVector<T>::End() const {
	if (storage) {
		return storage + alreadyUsed;
	}
	return nullptr;
}

template <typename U> 
void Swap(TVector<U> &first, TVector<U> &second) {
	using std::swap;

	swap(first.alreadyUsed, second.alreadyUsed);
	swap(first.storageSize, second.storageSize);
	swap(first.storage, second.storage);
}

template <typename T> 
TVector<T> &TVector<T>::operator=(TVector<T> other) {
	Swap(*this, other);

	return *this;
}

template <typename T> 
TVector<T>::~TVector() {
	alreadyUsed = storageSize = 0;
	delete[] storage;
	storage = nullptr;
}

template <typename T> typename 
TVector<T>::TValueType &TVector<T>::operator[](int index) const {
	if (index < 0 || index > alreadyUsed) {
		throw std::out_of_range("You are doing this wrong!");
	}

	return storage[index];
}

template <typename T> 
void TVector<T>::PushBack(TValueType &value) {
	if (alreadyUsed < storageSize) {
		storage[alreadyUsed] = value;
		++alreadyUsed;
		return;
	}

	unsigned int next_size = 1;
	if (storage) {
		next_size = storageSize * 2;
	}

	TVector<T> next{next_size};
	next.alreadyUsed = alreadyUsed;

	if (storage) {
		std::copy(storage, storage + storageSize, next.storage);
	}
	next.PushBack(value);
	Swap(*this, next);
}

template <typename U> 
TVector<U> CountingSort(const TVector<U> &unsortedVector, unsigned int max) {
	TVector<unsigned int> count{max + 1};
	for (register unsigned int i = 0; i <= max; i++) {
		count[i] = 0;
	}
	for (register unsigned int i = 0; i < unsortedVector.Size(); ++i) {
		++count[unsortedVector[i].key];
	}
	for (register unsigned int i = 1; i <= max; i++) {
		count[i] += count[i-1];
	}
	TVector<U> result{unsortedVector.Size()};
	for (register int i = unsortedVector.Size() - 1; i >= 0; i--) {
		result[--count[unsortedVector[i].key]] = unsortedVector[i];
	}

	return result;
} //Реализация сортировки подсчетом

int main()
{
    //std::ios::sync_with_stdio(false); //Опция std::ios_base::sync_with_stdio(false), кото-рая отключает синхронизацию потоков Си и С++
	//std::cin.tie(nullptr); //Опция std::cin.tie(nullptr) отделяет cin от cout
	TVector<TPair> input; //Вектор пар «ключ-значение»
	TPair temp;

	unsigned int maxKey = 0;
	while(std::cin >> temp.key >> temp.value) {
		input.PushBack(temp);
		if (temp.key > maxKey) {
			maxKey = temp.key;
		}
		temp.Fill();
	} //Ввод данных
  
    std::cout << "Count of lines is " << input.Size() << std::endl;

    // Измеряем время работы сортировки подсчётом.
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
	TVector<TPair> sortedVector = CountingSort(input, maxKey); //Сортировка подсчетом
    auto end_ts = std::chrono::system_clock::now();
    uint64_t counting_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();
    
    std::cout << "Counting sort time: " << counting_sort_ts << DURATION_PREFIX << std::endl;
 
}
