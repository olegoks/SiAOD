#include"SubjectIndex.h"
using namespace ndx;
void SubjectIndex::AddTermin(const std::string& name, const PageNumber page_number)
{

	list_.Add(name, page_number);

}

void SubjectIndex::AddUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const PageNumber page_number)
{

	for (uint index = 0; index < list_.size(); index++) {

		const ListElement& current_termin = list_[index];

		if (current_termin.name == termin_name) {

			current_termin.under_term_list_ptr->Add(under_termin_name, page_number);

			break;

		}

	}

}

void SubjectIndex::AddUnderUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const std::string& under_under_termin_name, const PageNumber page_number)
{



}

void SubjectIndex::DeleteTermin(const std::string& delete_termin_name) {

	list_.Delete(delete_termin_name);

}

void SubjectIndex::DeleteUnderTermin(const std::string& delete_termin_name, const std::string& delete_under_termin_name) {

	if (!list_.empty()) {
		
		unsigned int index = 0;
		std::string current_termin_name;

		do {

			const ListElement& list_element = list_[index];
			current_termin_name = list_element.name;

			index++;

		} while (current_termin_name != delete_termin_name);
	
		const ListElement& t_list_element = list_[index];
		TerminsList* ut_list = t_list_element.under_term_list_ptr;
		std::string current_under_termin_name;
		index = 0;

		do{

			const ListElement& under_termin_list_element = (*ut_list)[index];
			current_under_termin_name = under_termin_list_element.name;

			index++;

		} while (current_under_termin_name != delete_under_termin_name);

		(*ut_list).Delete(delete_under_termin_name);

	}

}

Termin SubjectIndex::SearchTermin(const std::string& search_termin_name) const
{

	bool termin_found = false, list_end = false;
	size_t list_size = list_.size();

	if (list_size == 0) throw SubjectIndexException("SubjectIndex is empty.");

	uint index = 0;

	while (!termin_found && !list_end) {

		const ListElement& cur_list_element = list_[index];

		termin_found = (cur_list_element.name == search_termin_name);
		
		index++;
		list_end = (index >= list_size);

	}

	index--;
	const uint FIRST_PAGE = 0;
	if (termin_found) return  Termin{ list_[index].name, (*list_[index].page_list_ptr)[FIRST_PAGE], list_[index].under_term_list_ptr };
		else
			throw SubjectIndexException("Element not found.");
	 
}

void SubjectIndex::Print() const
{
	
	for  (int termins_index = 0; termins_index < list_.size(); termins_index++)
	{

		const unsigned int FIRST_PAGE = 0;
		const ListElement& term_element = list_[termins_index];
		const std::string& term_name = term_element.name;
		const PageNumber term_page = (*term_element.page_list_ptr)[FIRST_PAGE];

		using namespace std;

		cout << term_name << ", " << term_page << endl;

		for (int under_termins_index = 0; under_termins_index < term_element.under_term_list_ptr->size(); under_termins_index++) {

			const ListElement& under_term_element = (*term_element.under_term_list_ptr)[under_termins_index];

			const  std::string& under_term_name = under_term_element.name;
			const PageNumber under_term_page = (*under_term_element.page_list_ptr)[FIRST_PAGE];

			cout << '\t' << under_term_name << ", " << under_term_page << endl;

		}
		
	}

}

void ndx::SubjectIndex::SortTerminsNames()
{

	list_.SortTerminsNames();

}

void ndx::SubjectIndex::EditTermin(const std::string& termin_name, const std::string& new_name, const PageNumber new_page)
{

	if (list_.size() == 0) throw SubjectIndexException("Subject index is empty.");
	
	bool termin_found = false;
	bool list_end = false;
	
	size_t index = 0;
	while (!termin_found && !list_end) {

		ListElement& edit_termin = list_[index];

		termin_found = (termin_name == edit_termin.name);
		list_end = (index >= list_.size());

		if (termin_found) {

			edit_termin.name = termin_name;
			(*edit_termin.page_list_ptr)[0] = new_page;

		}

	}

	if (!termin_found) throw SubjectIndexException("Element not found.");

}



SubjectIndex::SubjectIndex()noexcept : list_() {};

