#include <iostream>
#include "forward_list.h"
#include "double_linked_list.h"
#include <string>

int main(int argc, char* argv[])
{

	setlocale(LC_ALL, "Russian");
	
	using namespace lst;
	using namespace std;

	try {

		const unsigned int SIZE = 10;
		double_linked_list<string*> list;

		cout << "Введите номера телефона:" << endl;
		for (size_t i = 0; i < SIZE; i++)
		{
			string* input = new string;
			cin >> *input;
			list.push_back(input);

		}

		forward_list<string*> abonents;

		for (size_t i = 0; i < list.size(); i++)
			if (list[i]->size() == 7) 
				abonents.push_back(list[i]);

		cout << "Вывод списка абонентов" << endl;
		for (size_t i = abonents.size() - 1; i > 0; i--)
			cout << *abonents[i] << endl;

		cout << "Упорядоченный список номеров абонентов:" << endl;

		for (size_t i = 1; i < abonents.size(); i++)
		{
			for (size_t j = 0; j < abonents.size() - i; j++)
			{

				if (*abonents[j] < *abonents[j + 1]) {

					string* temp = abonents[j];
					abonents[j] = abonents[j + 1];
					abonents[j + 1] = temp;

				}
			}
		}

		cout << "Вывод списка абонентов:" << endl;
		for (size_t i = 0; i < abonents.size(); i++)cout << *abonents[i] << endl;
			
	}
	catch (forward_list<string*>::ListException error) {

		cerr <<"Error:" << error.GetError() << endl;
	}

	return EXIT_SUCCESS;

}


