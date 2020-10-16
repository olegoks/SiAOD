#include"SubjectIndex.h"
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

Termin SubjectIndex::SearchTermin(const string& search_termin_name) const
{
	try {

		return termins_[TerminName(search_termin_name)];

	}
	catch (TerminException exception) {

		throw SubjectIndexException(exception.What());

	}
	 
}

void SubjectIndex::Print() const
{
	using std::cout;
	using std::endl;

	for (auto it = termins_info_.begin(); it != termins_info_.end(); it++){

		const Termin& current_termin = termins_[TerminName((*it)->GetName())];
		cout << current_termin.GetPrintString() << endl;

		try {

		TerminsList& under_termins = current_termin.GetUnderTerminsList();

		for (size_t index_ut = 0; index_ut < under_termins.GetNumberOfTermins(); index_ut++)
		{
			const Termin& under_termin = under_termins[index_ut];
			cout << '\t' << under_termin.GetPrintString() << endl;

			try {

			TerminsList under_under_termins = under_termin.GetUnderTerminsList();

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

		termins_[TerminName(termin_name)].Edit(new_name, new_page);
	
	}
	catch (mp::MapException exception) {

		using std::cout;
		using std::endl;
		cout << exception.GetError() << endl;

	}
	
}



SubjectIndex::SubjectIndex()noexcept : termins_(100) {};

