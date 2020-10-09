
#include "multimap.h"
#include <string>
#include <iostream>

class stringKey :public std::string {
private:
protected:
public:

	int operator= (const stringKey& string) {
		return (int)string[0];
	}
	stringKey(const char* const_string)noexcept: std::string(const_string){

	}

	stringKey():std::string() {

	}

};

int main() {

	using namespace mltmp;
	using namespace std;

	setlocale(LC_ALL, "Russian");

	multimap<stringKey, stringKey> termins(10);
	cout << " Введите ключ и значени:" << endl;
	stringKey key, value;
	cin >> key >> value;
	termins.Add(key, value);//stringKey("termin_1"), stringKey("podtermin_1"));
	cout << "["<< key <<"] = " << termins[key];
	return EXIT_SUCCESS;
}