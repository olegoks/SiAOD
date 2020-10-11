#include"SubjectIndex.h"
using namespace ndx;
void ndx::SubjectIndex::AddTermin(const std::string& name, const PageNumber page_number)
{

	ListElement list_element;

	list_element.name = name;
	list_element.under_term_list_ptr = (lst::forward_list<ListElement>*) new lst::forward_list<ListElement>();
	list_element.page_list_ptr = (lst::forward_list<PageNumber>*) new lst::forward_list<PageNumber>();
	list_element.page_list_ptr->push_back(page_number);

	list_.push_back(list_element);

}

void ndx::SubjectIndex::AddUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const PageNumber page_number)
{

	for (uint index = 0; index < list_.size(); index++) {

		ListElement& current_termin = list_[index];

		if (current_termin.name == termin_name) {

			ListElement under_termin;
			under_termin.name = under_termin_name;
			under_termin.page_list_ptr = (lst::forward_list<PageNumber>*) new lst::forward_list<PageNumber>();
			under_termin.page_list_ptr->push_back(page_number);
			under_termin.under_term_list_ptr = (lst::forward_list<ListElement>*) new lst::forward_list<ListElement>();
			current_termin.under_term_list_ptr->push_back(under_termin);

			break;

		}

	}

}

SubjectIndex::SubjectIndex()noexcept : list_() {};

