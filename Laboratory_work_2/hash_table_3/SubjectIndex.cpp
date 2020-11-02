#include"SubjectIndex.h"
#include<fstream>
#include<algorithm>

void SubjectIndex::AddTermin(const string& name, const PageNumber page_number)
{
	
	termins_.Add(TerminName(name), Termin(name, page_number));
	termins_info_.push_back(&termins_[TerminName(name)]);

}

void SubjectIndex::AddUnderTermin(const string& termin_name, const string& under_termin_name, const PageNumber page_number)
{
	try {

		Termin& termin = termins_[TerminName(termin_name)];
		termin.AddUnderTermin(under_termin_name, page_number);

	}
	catch (mp::MapException exception) {

		using std::cout;
		using std::endl;

		cout << exception.GetError() << endl;

	}
	
}

void SubjectIndex::AddUnderUnderTermin(const string& termin_name, const string& under_termin_name, const string& under_under_termin_name, const PageNumber page_number) {

	using std::cout;
	using std::endl;

	try {

		Termin& termin = termins_[TerminName(termin_name)];
		TerminsList& under_termins = termin.GetUnderTerminsList();
		const size_t under_termins_number = under_termins.GetNumberOfTermins();

		for (size_t index = 0; index < under_termins_number; index++)
		{
			Termin& cur_u_termin = under_termins[index];

			if (cur_u_termin.GetName() == under_termin_name) {

				cur_u_termin.AddUnderTermin(under_under_termin_name, page_number);

			}

		}

	}
	catch (mp::MapException map) {
		
		cout << map.GetError() << endl;

	}
	catch (TerminsListException termins_list) {

		cout << termins_list.What() << endl;

	}

}

void SubjectIndex::DeleteTermin(const string& delete_termin_name) {

	try {

		for (auto it = termins_info_.begin(); it != termins_info_.end(); it++) {

			if ((*it)->GetName()== delete_termin_name) {
				termins_info_.erase(it);
				break;
			}

		}

		termins_.Delete(TerminName(delete_termin_name));

	}
	catch (TerminsListException exception) {

		throw SubjectIndexException(exception.What());

	}

}

void SubjectIndex::DeleteUnderTermin(const string& delete_termin_name, const string& delete_under_termin_name) {

	try {

		termins_[TerminName(delete_termin_name)].DeleteUnderTermin(delete_under_termin_name);
	
	}
	catch (TerminsListException exception) {

		throw SubjectIndexException(exception.What());

	}

}

forward_list<const Termin*>* SubjectIndex::SearchTerminByUnderTermin(const string& under_termin_name)const {
	
	bool termin_found = false;
	forward_list<const Termin*>* search_termins_list = new forward_list<const Termin*>;

	for (auto it = termins_info_.begin(); it < termins_info_.end(); it++)
	{

		const Termin* const current_termin = (*it);
		try {

			TerminsList& under_termins = current_termin->GetUnderTerminsList();

			for (size_t index = 0; index < under_termins.GetNumberOfTermins(); index++){

				const Termin& under_termin = under_termins[index];

				if (under_termin.GetName() == under_termin_name) 
					search_termins_list->push_back(current_termin);

			}

		}catch (TerminException exception) {}
		
	}

	return search_termins_list;

}

Termin SubjectIndex::SearchTermin(const string& search_termin_name) const
{
	try {

		return termins_[TerminName(search_termin_name)];

	}
	catch (mp::MapException exception) {

		throw SubjectIndexException(exception.GetError());

	}
	 
}

Termin ProcessLine(const string& termin_line) {

	using std::string;
	
	const char kSpace = ' ';
	const char kComma = ',';

	int pos = termin_line.find(kComma);
	string termin_name = termin_line.substr(0, pos);
	size_t index = 0;
	while (termin_name[0] == '\t')termin_name.erase(0, 1);
	pos = termin_line.find(kComma) + 1;
	int page_number = 0;

	if (pos != 0) 
		page_number = stoi(termin_line.substr(pos));

	return Termin(termin_name, page_number);

}

size_t NestingLevel(const string& line) {

	if (!line.empty()) {

		int index = 0;
		while (line[index] == '\t') index++;

		return index;

	}

	return 0;

}

void SubjectIndex::ReadFile(const string& file_name)
{

	using namespace std;

	const size_t kMaxLineLength = 100;
	
	ifstream file;

	file.open(file_name, ios::in);

	char line[kMaxLineLength];
	string termin_s, u_termin_s, uu_termin_s;

	while (file.getline(line, kMaxLineLength)) {

		const size_t line_nesting_level = NestingLevel(string(line));

		Termin termin;

		switch (line_nesting_level){
		case 0: {
			
			
			termin = ProcessLine(line);
			termin_s = termin.GetName();
			SubjectIndex::AddTermin(termin_s, termin.GetPage(0));

			break;
		}
		case 1: {

			termin = ProcessLine(line);
			u_termin_s = termin.GetName();
			SubjectIndex::AddUnderTermin(termin_s, u_termin_s, termin.GetPage(0));

			break;
		}
		case 2: {

			termin = ProcessLine(line);
			uu_termin_s = termin.GetName();
			SubjectIndex::AddUnderUnderTermin(termin_s, u_termin_s, uu_termin_s, termin.GetPage(0));

			break;
		}

		}

	}

	file.close();

}

void SubjectIndex::Print() const
{
	using std::cout;
	using std::endl;

	for (auto it = termins_info_.begin(); it != termins_info_.end(); it++){
		std::string termin_name = (*it)->GetName();
		const Termin& current_termin = termins_[TerminName(termin_name)];
		cout << current_termin.GetPrintString() << endl;

		try {

		TerminsList& under_termins = current_termin.GetUnderTerminsList();

		for (size_t index_ut = 0; index_ut < under_termins.GetNumberOfTermins(); index_ut++)
		{
			const Termin& under_termin = under_termins[index_ut];
			cout << '\t' << under_termin.GetPrintString() << endl;

			try {

			TerminsList& under_under_termins = under_termin.GetUnderTerminsList();

			for (size_t index_uut = 0; index_uut < under_termin.GetNumberOfPages(); index_uut++){

				const Termin& under_under_termin = under_under_termins[index_uut];
				cout << "\t\t" << under_under_termin.GetPrintString() << endl;

			}

			}
			catch (TerminException exception) {}

			}

		}
		catch (TerminException exception) {}

	}
}

static bool CompareNames(const Termin* const first_termin, const Termin* const second_termin) {

	return first_termin->GetName() < second_termin->GetName();

}

static bool ComparePages(const Termin* const first_termin, const Termin* const second_termin) {

	return first_termin->GetPage(0) < second_termin->GetPage(0);

}

void SubjectIndex::SortTerminsNames()
{

	sort(termins_info_.begin(), termins_info_.end(), CompareNames);

}

void SubjectIndex::SortPages() {

	sort(termins_info_.begin(), termins_info_.end(), ComparePages);

}

void SubjectIndex::EditTermin(const string& termin_name, const string& new_name, const PageNumber new_page)
{
	
	try {
		
		Termin termin = std::move(termins_[TerminName(termin_name)]);
		
		for (auto it = termins_info_.begin(); it != termins_info_.end(); it++)
		{

			if ((*it)->GetName() == termin_name) {
				termins_.Delete(TerminName(termin.GetName()));
				termin.Edit(new_name, new_page);
				termins_.Add(TerminName(termin.GetName()), termin);
				(*it) = &termins_[TerminName(termin.GetName())];

				break;
			}
			
		}

	}
	catch (mp::MapException exception) {

		using std::cout;
		using std::endl;
		cout << exception.GetError() << endl;

	}
	
}

SubjectIndex::SubjectIndex()noexcept : termins_(5) {};

