
#include <string>
#include <iostream>
#include "TermBase.h"

int main() {

	using namespace std;
	setlocale(LC_ALL, "ru");
	TermBase term_base;
	term_base.ReadTermsFile("terms.txt");


	return EXIT_SUCCESS;

}