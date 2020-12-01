#include "BinaryTree.hpp"
#include <iostream>

void ShowVertex(const BinaryTree<int>::Vertex& vertex)noexcept(true) {



}
int main() {

	setlocale(LC_ALL, "ru");
	BinaryTree<int> btree{ 8, 12, 4, 6, 5, 3, 11, 9, 16 };

	btree.SetProcessVertexFunc([](const BinaryTree<int>::Vertex& vertex)->void { std::cout << "(" <<vertex.data_ << ") "; });

	std::cout << "Прямой обход:" << std::endl;
	btree.TraversePreorder();
	std::cout << std::endl;

	std::cout << "Обратный обход:" << std::endl;
	btree.TraversePostorder();
	std::cout << std::endl;

	std::cout << "Симметричный обход:" << std::endl;
	btree.TraverseInorder();
	std::cout << std::endl;

	return 0;
}