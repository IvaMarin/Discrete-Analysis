#ifndef AVLTREE_HPP
#define AVLTREE_HPP

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
	unsigned long long height(const TAVLNode *node) {
		return node != nullptr ? node->height : 0;
	}

	//Вспомогательная функция для вычисления максимального эл-та
	template<class T> 
	const T& Max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

	//Функция для корректировки данных о высоте данного узла
	void Reheight(TAVLNode *node) {
		node->height = Max(height(node->left), height(node->right)) + 1;
	}

	//Функция для вычисления баланса данного узла
	int Balance(const TAVLNode *node) {
		return height(node->left) - height(node->right);
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
				return nullptr;
			}
			return node;
		}
		if (k < node->key) {
			node->left = Insert(node->left, k, v);
		}
		else if (k > node->key) {
			node->right = Insert(node->right, k, v);
		}
		else {
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
				return nullptr;
			}
			if (rightChild == nullptr) {
				delete node;
				return leftChild;
			}
			if (leftChild == nullptr) {
				delete node;
				return rightChild;
			}
			node->right = RemoveMin(node, rightChild);
		}
		return Rebalance(node);
	}

	//Поиск узла в АВЛ-дереве
	TAVLNode *Search(TAVLNode *node, K k) {
		if (node == nullptr) {
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
				return current;
			}
		}
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

}; 

#endif /* AVLTREE_HPP */


