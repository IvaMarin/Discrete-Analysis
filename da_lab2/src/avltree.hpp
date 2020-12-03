#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>

#include "string.hpp"

template<class K, class V> 
class TAVLTree {
public:
	//Узел АВЛ-дерева  
	struct TAVLNode {
		K key; //Ключ узла
		V value; //Значение в узле
		unsigned long long height; //Высота поддерева с корнем в данном узле
		TAVLNode *left; //Указатель на левое поддерево
		TAVLNode *right; //Указатель на правое поддерево
		TAVLNode() : key(), value(), height{1}, left{nullptr}, right{nullptr} {}; //Конструктор по умолчанию
		TAVLNode(K key, V value) : key{key}, value{value}, height{1}, left{nullptr}, right{nullptr} {}; //Конструктор
		~TAVLNode() {}; //Деструктор
	};

	TAVLNode *root; //Корень АВЛ-дерева
	
	//Функция для вычисления высоты поддерева с корнем в данном узле
	unsigned long long Height(const TAVLNode *node) {
		return node != nullptr ? node->height : 0;
	}

	//Вспомогательная функция для вычисления максимального эл-та
	template<class T> 
	const T& Max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

	//Функция для корректировки данных о высоте данного узла
	void Reheight(TAVLNode *node) {
		node->height = Max(Height(node->left), Height(node->right)) + 1;
	}

	//Функция для вычисления баланса данного узла
	int Balance(const TAVLNode *node) {
		return Height(node->left) - Height(node->right);
	}

	//Левый попворот относительного данного узла
	TAVLNode *RotateLeft(TAVLNode *x) {
		TAVLNode *y = x->right;
		x->right = y->left;
		y->left = x;
		Reheight(x);
		Reheight(y);
		return y;
	}

	//Правый поворот относительно данного узла
	TAVLNode *RotateRight(TAVLNode *y) {
		TAVLNode *x = y->left;
		y->left = x->right;
		x->right = y;
		Reheight(y);
		Reheight(x);
		return x;
	}

	//Болшой левый поворот (правый поворот отн-но правого дочернего узла + левый поворот отн-но данного узла)
	TAVLNode *BigRotateLeft(TAVLNode *x) {
		x->right = RotateRight(x->right);
		return RotateLeft(x);
	}

	//Болшой правый поворот (левый поворот отн-но левого дочернего узла + правый поворот отн-но данного узла)
	TAVLNode *BigRotateRight(TAVLNode *x) {
		x->left = RotateLeft(x->left);
		return RotateRight(x);
	}

	//Перебалансировка дерева
	TAVLNode *Rebalance(TAVLNode *node) {
		if (node == nullptr) {
			return nullptr;
		}
		Reheight(node);
		int currentBalance = Balance(node);
		if (currentBalance == -2) {
			if (Balance(node->right) == 1) {
				return BigRotateLeft(node); //Правый-Левый случай
			}
			return RotateLeft(node); //Правый-Правый случай
		}
		else if (currentBalance == 2) {
			if (Balance(node->left) == -1) {
				return BigRotateRight(node); //Левый-Правый случай
			}
			return RotateRight(node); //Левый-Левый случай
		}
		return node; //Балансировка не требуется
	}

	//Вставка узла в АВЛ-дерево
	TAVLNode *Insert(TAVLNode *node, K k, V v) {
	if (node == nullptr) { //Если дерево пустое, тогда создадим корень
			try {
				node = new TAVLNode(k, v);
			}
			catch (std::bad_alloc &e) {
				std::cout << "ERROR: " << e.what() << std::endl;
				return nullptr;
			}
			std::cout << "OK" << std::endl;
			return node;
		}
		if (k < node->key) {
			node->left = Insert(node->left, k, v);
		}
		else if (k > node->key) {
			node->right = Insert(node->right, k, v);
		}
		else {
			std::cout << "Exist" << std::endl;
		}
		return Rebalance(node);
	}

	//Поиск и удаление узла с минимальным ключом
	TAVLNode *RemoveMin(TAVLNode *node, TAVLNode *currentNode) {
		if (currentNode->left != nullptr) {
			currentNode->left = RemoveMin(node, currentNode->left);
		}
		else {
			TAVLNode *rightChild = currentNode->right;
			node->key = std::move(currentNode->key);
			node->value = currentNode->value;
			delete currentNode;
			currentNode = rightChild;
		}
		return Rebalance(currentNode);
	}

	//Удаление узла в АВЛ-дереве
	TAVLNode *Remove(TAVLNode *node, K k) {
		if (node == nullptr) {
			std::cout << "NoSuchWord"<< std::endl;
			return nullptr;
		}
		if (k < node->key) {
			node->left = Remove(node->left, k);
		}
		else if (k > node->key) {
			node->right = Remove(node->right, k);
		}
		else {
			TAVLNode *leftChild = node->left;
			TAVLNode *rightChild = node->right;
			if (leftChild == nullptr && rightChild == nullptr) {
				delete node;
				std::cout << "OK" << std::endl;
				return nullptr;
			}
			if (rightChild == nullptr) {
				delete node;
				std::cout << "OK" << std::endl;
				return leftChild;
			}
			if (leftChild == nullptr) {
				delete node;
				std::cout << "OK" << std::endl;
				return rightChild;
			}
			node->right = RemoveMin(node, rightChild);
			std::cout << "OK" << std::endl;
		}
		return Rebalance(node);
	}

	//Поиск узла в АВЛ-дереве
	TAVLNode *Search(TAVLNode *node, K k) {
		if (node == nullptr) {
			std::cout << "NoSuchWord" << std::endl;
			return nullptr;
		}
		for (TAVLNode *current = node; current != nullptr; ) {
			if (k < current->key) {
				current = current->left;
			}
			else if (k > current->key) {
				current = current->right;
			}
			else {
				std::cout << "OK: " << current->value << std::endl;
				return current;
			}
		}
		std::cout << "NoSuchWord" << std::endl;
		return nullptr;
	}

public:
	TAVLTree() : root(nullptr) {}; //Конструктор

	void Add(K k, V v) { //Метод добавления в дерево
		root = Insert(root, std::move(k), v);
	}

	void Delete(K k) { //Метод удаления из дерева
		root = Remove(root, std::move(k));
	}

	TAVLNode *Find(K k) { //Метод нахождения узла в дереве
		return Search(root, std::move(k));
	}

	void TreeDelete(TAVLNode *node) { //Метод удаления дерева
		if (node != nullptr) {
			TreeDelete(node->left);
			TreeDelete(node->right);
			delete node;
		}
	}

	~TAVLTree() { //Деструктор
		TreeDelete(root);
	}

	void Save(std::ostream &os, const TAVLNode *node) { //Метод сохранения дерева в файл
		if (node == nullptr) {
			return;
		}
		int keySize = node->key.Size();
		os.write(reinterpret_cast<char *>(&keySize), sizeof(keySize));
		os.write(node->key.Cstr(), keySize);
		os.write((char *)&node->value, sizeof(node->value));

		bool hasLeft = node->left != nullptr;
		bool hasRight = node->right != nullptr;

		os.write(reinterpret_cast<char *>(&hasLeft), sizeof(hasLeft));
		os.write(reinterpret_cast<char *>(&hasRight), sizeof(hasRight));

		if (hasLeft) {
			Save(os, node->left);
		}
		if (hasRight) {
			Save(os, node->right);
		}
	}

	TAVLNode *Load(std::istream &is, const TAVLNode *node) { //Метод загрузки дерева из файла
		(void)(node);
		TAVLNode *root = nullptr;

		int keySize;
		is.read(reinterpret_cast<char *>(&keySize), sizeof(keySize));

		if (is.gcount() == 0) {
			return root;
		}

		char *key = new char[keySize + 1];
		key[keySize] = '\0';
		is.read(key, keySize);

		uint64_t value;
		is.read(reinterpret_cast<char *>(&value), sizeof(value));

		bool hasLeft = false;
		bool hasRight = false;
		is.read(reinterpret_cast<char *>(&hasLeft), sizeof(hasLeft));
		is.read(reinterpret_cast<char *>(&hasRight), sizeof(hasRight));

		root = new TAVLNode();
		root->key.CstrMove(key);
		root->value = value;

		if (hasLeft) {
			root->left = Load(is, root);
		}
		else {
			root->left = nullptr;
		}

		if (hasRight) {
			root->right = Load(is, root);
		}
		else {
			root->right = nullptr;
		}

		return root;
	}

	bool OpenFileSave(TString &fileName) { //Метод открытия файла для сохранения
		std::ofstream os{fileName.Cstr(), std::ios::binary | std::ios::out};
		if (os) {
			Save(os, root);
		} 
		else {
			return false;
		}
		os.close();
		return true;
	}

	bool OpenFileLoad(TString &fileName) { //Метод открытия файла для загрузки
		std::ifstream is{fileName.Cstr(), std::ios::binary | std::ios::in};
		if (is) {
			TreeDelete(root);
			root = Load(is, nullptr);
		}
		else {
			return false;
		}
		is.close();
		return true;
	}
	
}; 

#endif /* AVLTREE_HPP */


