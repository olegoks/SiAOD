#include"TermBase.h"
#include <fstream>

Termin::Termin(const char* const_string, const PageNumber page_number)noexcept :
	term_name_(const_string),
	page_number_(page_number),
	under_terms_() {

}

Termin::Termin()noexcept :
	term_name_(DEFAULT_TERMIN_NAME),
	page_number_(DEFAULT_PAGE_NUMBER),
	under_terms_() {

}


bool TermBase::ReadTermsFile(const char* file_name) {

	using namespace std;
	ifstream file;

	file.open(file_name, ios::in);

	if (!file.is_open()) return false;

	char line[100];
	string termin, under_termin, under_under_termin;

	while (file.getline(line, 100)) {

		int index = 0;
		while (line[index] == '\t') index++;

		switch (index) {
		case 0: {

			termin = line;
			under_termin = "";
			under_under_termin = "";

			break;
		}
		case 1: {

			
			under_termin = line;
			under_under_termin = "";

			break;
		}
		case 2: {

			under_under_termin = line;

			break;
		}
		};
		

		

	}



}