#include "BinaryTree.hpp"
#include <iostream>

void ShowVertex(const BinaryTree<int>::Vertex& vertex)noexcept(true) {



}
int main() {

	BinaryTree<int> btree{ 1, 2, 3, 4, 0, 6 };

	btree.SetProcessVertexFunc([](const BinaryTree<int>::Vertex& vertex)->void { std::cout << vertex.data_; });

	std::cout << "������ �����:" << std::endl;
	btree.TraversePreorder();
	std::cout << "�������� �����:" << std::endl;
	btree.TraversePostorder();
	std::cout << "������������ �����:" << std::endl;
	btree.TraverseInorder();

	return 0;
}