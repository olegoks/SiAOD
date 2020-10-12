
#include "SubjectIndex.h"
#include <fstream>

std::string RetTermName(char line[]) {

	using namespace std;
	string line_s(line);
	int pos = line_s.find(",");
	line_s = line_s.substr(0, pos);
	size_t index = 0;

	while ((index = line_s.find("  ")) != std::string::npos)line_s.erase(index, 1);

	return line_s;

}

unsigned int RetPageNumber(char line[]) {

	using namespace std;
	string line_s(line);
	int pos = line_s.find(",") + 1;
	int number = 0;

	if (pos != 0) {

		line_s = line_s.substr(pos);
		number = std::stoi(line_s);

	}

	return number;

}
bool ReadLaforeSubjectIndex(ndx::SubjectIndex* subject_index) {

	using namespace std;
	ifstream file;

	file.open("terms.txt", ios::in);

	if (!file.is_open()) return false;

	char line[100];

	string termin, under_termin, under_under_termin;

	while (file.getline(line, 100)) {

		int index = 0;
		while (line[index] == '\t') index++;

		int page;

		switch (index) {
		case 0: {

			termin = RetTermName(line);
			page = RetPageNumber(line);
			subject_index->AddTermin(termin, page);

			break;
		}

		case 1: {

			under_termin = RetTermName(line);
			page = RetPageNumber(line);
			subject_index->AddUnderTermin(termin, under_termin, page);

			break;
		}

		case 2: {

			under_under_termin = RetTermName(line);
			page = RetPageNumber(line);
			subject_index->AddUnderUnderTermin(termin, under_termin, under_under_termin, page);

			break;
		}

		};

	}

}


int main() {

	setlocale(LC_ALL, "ru");
	ndx::SubjectIndex subject_index;
	ReadLaforeSubjectIndex(&subject_index);
	subject_index.Print();
	subject_index.DeleteTermin("функции");
	std::cout << std::endl << std::endl << std::endl;
	subject_index.Print();
	
	return 0;

}