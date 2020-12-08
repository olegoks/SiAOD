#include <vector>
#include <iostream>

using AdjacencyMatrix = std::vector<std::vector<int>>;

int main() {

	setlocale(LC_ALL, "ru");
	std::cout << "Размер матрицы смежности(N): ";
	size_t size;
	std::cin >> size;
	std::cout << "Введите матрицу смежности: " << std::endl;
	AdjacencyMatrix adjacency_matrix;

	adjacency_matrix.reserve(size);
	for (size_t i = 0; i < size; i++){

		adjacency_matrix.push_back(std::vector<int>{});
		adjacency_matrix[i].reserve(size);

	}
	
	for (auto& arr : adjacency_matrix) {

		for (size_t j = 0; j < size; j++) {

			int input = 0;
			std::cin >> input;
			arr.push_back(input);

		}

	}

	
	return 0;
}