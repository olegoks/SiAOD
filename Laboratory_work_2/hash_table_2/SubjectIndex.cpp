#include"SubjectIndex.h"
#include <fstream>

Termin::Termin(const TermName over_term_name, const TermName term_name, const TermName under_term_name, const PageNumber page_number)noexcept :
	over_term_(over_term_name),
	term_(term_name),
	under_term_(under_term_name),
	page_(page_number)
{

}

Termin::Termin()noexcept :
	under_term_(DEFAULT_TERMIN_NAME),
	term_(DEFAULT_TERMIN_NAME),
	over_term_(DEFAULT_TERMIN_NAME),
	page_(DEFAULT_PAGE_NUMBER)
{

}

SubjectIndex::SubjectIndex(const uint depth)noexcept {

	for (uint i = 0; i < depth; i++) levels_.push_back((Map*) new Map(DEFAULT_MAP_SIZE));

}

void SubjectIndex::Add(Termin termin, Termin under_termin, Termin under_under_termin)
{

	
	(*levels_[1])[under_termin.GetName()].SetUnderTermName(under_under_termin.GetName());
	levels_[2]->Add(under_under_termin.GetName(), under_under_termin);

}

void SubjectIndex::Add(Termin termin, Termin under_termin)
{

	(*levels_[0])[termin.GetName()].SetUnderTermName(under_termin.GetName());
	levels_[1]->Add(under_termin.GetName(), under_termin);
	
}

void SubjectIndex::Add(Termin termin)
{

	levels_[0]->Add(termin.GetName(), termin);

}

//bool SubjectIndex::ReadTermsFile(const char* file_name) {
//
//	//using namespace std;
//	//ifstream file;
//
//	//file.open(file_name, ios::in);
//
//	//if (!file.is_open()) return false;
//
//	//char line[100];
//	//string termin, under_termin, under_under_termin;
//
//	//while (file.getline(line, 100)) {
//
//	//	int index = 0;
//	//	while (line[index] == '\t') index++;
//
//	//	switch (index) {
//	//	case 0: {
//
//	//		termin = line;
//	//		under_termin = "";
//	//		under_under_termin = "";
//
//	//		break;
//	//	}
//	//	case 1: {
//
//	//		
//	//		under_termin = line;
//	//		under_under_termin = "";
//
//	//		break;
//	//	}
//	//	case 2: {
//
//	//		under_under_termin = line;
//
//	//		break;
//	//	}
//	//	};
//
//	//	Termin term
//	//	termins_.Add(termin, );
//	//	
//
//	//	
//
//	//}
//
//
//
//}