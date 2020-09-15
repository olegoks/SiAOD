#include <iostream>
#include "forward_list.h"
#include "double_linked_list.h"
#include <string>
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	{
		using namespace lst;
		using namespace std;

		try {

			const unsigned int SIZE = 5;
			double_linked_list<string*> list;

			for (size_t i = 0; i < SIZE; i++)
			{
				string* input = new string;
				std::cout << "Введите значение:" << std::endl;
				std::cin >> *input;
				list.push_back(input);

			}

			int index = list.size() - 1;

			while (index >= 0) {

				string* element = list[index];
				cout << *element << endl;
				index--;

			}

			forward_list<string* > abonents;
			cout << "Вывод обонентов:" << endl;
			for (size_t i = 0; i < SIZE; i++)
			{
				if (list[i]->size() == 7) {
					cout << *list[i] << endl;
					abonents.push_back(list[i]);
				}

			}
			cout << "отсортированные абоненты" << endl;

			for (size_t i = 0; i < abonents.size() - 1; i++)
			{
				for (size_t j = 0; j < abonents.size() - 2; j++)
				{

					if (*abonents[j] < * abonents[j + 1]) {

						string* temp = abonents[j];
						abonents[j] = abonents[j + 1];
						abonents[j + 1] = abonents[j];

					}

				}
			}

			for (size_t i = 0; i < abonents.size(); i++)
			{
				cout << *abonents[i] << endl;
			}

		}

		catch (forward_list<int>::ListException error) {

			std::cerr <<"Error:" << error.GetError() << std::endl;

		}

	}

	system("pause");

}


