#include "ring_list.h"
#include <iostream>

int main() {

	using namespace std;
	using namespace rng;
	setlocale(LC_ALL, "Russian");
	uint interval;
	cin >> interval;

	ring_list* list = (ring_list*) new ring_list;

	for (uint i = 1; i <= 64; i++)
	{
		list->create(i);

		uint counter = 0;
		rng::iterator it = list->begin();

		while (list->size() > 1) {

			counter++;
			if (counter > interval)counter = 1;

			if (counter == interval) {
				cout <<" "<< *it;
				list->erase(it);
			}
			else
				++it;
		}

		it = list->begin();
		cout << ":   Номер последнего игрока:" << *it << endl << endl;
		list->clear();
	}
	system("pause");
	return 0;
}