#include "BinaryTree.hpp"
#include "LinkedBinaryTree.hpp"
#include <iostream>
#include <vector>

int main() {

	setlocale(LC_ALL, "ru");
	std::cout << "Введите числа: ";

	BinaryTree<int> btree;

	bool is_input = true;

	std::vector<int> input_list;//{5, 2, 6, 1, 4, 9, 7, 3};

	while (is_input) {

		int input = 0;
		
		std::cin >> input;

		if (input == 0)
			is_input = false;
		else
			//btree.Add(input);
			input_list.push_back(input);
	}

	for (auto& obj : input_list)
		btree.Add(obj);

	std::cout << std::endl;
	btree.print_tree();

	btree.SetProcessVertexFunc([](const BinaryTree<int>::Vertex& vertex)->void { std::cout << "(" <<vertex.data_ << ")"; });

	std::cout << "Прямой обход:" << std::endl;
	btree.TraversePreorder();
	std::cout << std::endl;

	std::cout << "Обратный обход:" << std::endl;
	btree.TraversePostorder();
	std::cout << std::endl;

	std::cout << "Симметричный обход:" << std::endl;
	btree.TraverseInorder();
	std::cout << std::endl;

	LinkedBinaryTree<int> linkedBtree{};

	for (auto& obj : input_list)
		linkedBtree.Add(obj);

	std::cout << "Прошитое бинарное дерево: " << std::endl;
	linkedBtree.print_tree();

	bool is_delete = true;

	while (is_delete) {

		int input = 0;

		std::cout << "Введите элемент, который нужно удалить: ";
		std::cin >> input;

		if (input == 0)
			is_delete = false;
		else {

			linkedBtree.Delete(input);
			std::cout << "Дерево после удаления: " << std::endl;
			linkedBtree.print_tree();
			std::cout << std::endl;

		}

	}
	

	return 0;
}