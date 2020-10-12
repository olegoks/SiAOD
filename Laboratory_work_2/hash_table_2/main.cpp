
#include <string>
#include <iostream>
#include "SubjectIndex.h"
#include <fstream>


const unsigned int SUBJECT_INDEX_DEPTH = 3;

std::string RetTermName(char line[]) {

	using namespace std;
	string line_s(line);
	int pos = line_s.find(",");
	line_s = line_s.substr(0, pos);
	size_t index = 0;

	while ((index = line_s.find(' ')) != std::string::npos)
		line_s.erase(index, 1);

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
bool ReadLaforeSubjectIndex(SubjectIndex* subject_index) {

	using namespace std;
	ifstream file;

	file.open("terms.txt", ios::in);

	if (!file.is_open()) return false;

	char line[100];

	Termin termin, under_termin, under_under_termin;

	while (file.getline(line, 100)) {

		int index = 0;
		while (line[index] == '\t') index++;

		{
		int page;

			switch (index) {
			case 0: {

				page = RetPageNumber(line);
				termin.SetTermName(RetTermName(line));
				subject_index->Add(termin);
				break;
			}
			case 1: {

				page = RetPageNumber(line);
				under_termin.SetTermName(RetTermName(line));
				subject_index->Add(termin, under_termin);
				break;
			}
			case 2: {

				page = RetPageNumber(line);
				under_under_termin.SetTermName(RetTermName(line));
				subject_index->Add(termin, under_termin, under_under_termin);

				break;
			}

			case 3: {



				break;
			}
			};

		}


	}

}

int main() {

	using namespace std;
	setlocale(LC_ALL, "ru");

	SubjectIndex term_base(SUBJECT_INDEX_DEPTH);
	ReadLaforeSubjectIndex(&term_base);
	//term_base.Add();
	//term_base.ReadTermsFile("terms.txt");


	return EXIT_SUCCESS;

}