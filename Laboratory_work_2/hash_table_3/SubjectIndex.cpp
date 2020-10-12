#include"SubjectIndex.h"
using namespace ndx;
void ndx::SubjectIndex::AddTermin(const std::string& name, const PageNumber page_number)
{

	list_.Add(name, page_number);

}

void ndx::SubjectIndex::AddUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const PageNumber page_number)
{

	for (uint index = 0; index < list_.size(); index++) {

		const ListElement& current_termin = list_[index];

		if (current_termin.name == termin_name) {

			current_termin.under_term_list_ptr->Add(under_termin_name, page_number);

			break;

		}

	}

}

void ndx::SubjectIndex::AddUnderUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const std::string& under_under_termin_name, const PageNumber page_number)
{



}

void ndx::SubjectIndex::DeleteTermin(const std::string& delete_termin_name) {

	list_.Delete(delete_termin_name);

}

void ndx::SubjectIndex::DeleteUnderTermin(const std::string& delete_termin_name, const std::string& delete_under_termin_name) {

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

void ndx::SubjectIndex::Print() const
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

SubjectIndex::SubjectIndex()noexcept : list_() {};

