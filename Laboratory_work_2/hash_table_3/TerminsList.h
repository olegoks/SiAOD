#pragma once
#ifndef _TERMINS_LIST_H_
#define _TERMINS_LIST_H_

#include "forward_list.h"
#include <string>

using uint = unsigned int;
using PageNumber = uint;

static const std::string DEFAULR_TERM_NAME = "Default.";

class TerminsList;

static class ListElement {

public:

	TerminsList* under_term_list_ptr;
	lst::forward_list<PageNumber>* page_list_ptr;

	std::string name;

	ListElement()noexcept :
		name(DEFAULR_TERM_NAME),
		under_term_list_ptr(nullptr),
		page_list_ptr(nullptr) {

	}

	ListElement(const std::string& _name, const PageNumber page_number)noexcept :
		name(_name),
		under_term_list_ptr(nullptr),
		page_list_ptr(nullptr) {

	}

};

static bool CompareNames(const ListElement& first_element, const ListElement& second_element) {

	return first_element.name > second_element.name;

}
static bool ComparePages(const ListElement& first_element, const ListElement& second_element) {

	const PageNumber first_page = (first_element.page_list_ptr->empty()) ? 0 : (*first_element.page_list_ptr)[0];
	const PageNumber second_page = (second_element.page_list_ptr->empty()) ? 0 : (*second_element.page_list_ptr)[0];
	
	return  first_page < second_page;
}

class TerminsList:public lst::forward_list<ListElement> {

	typedef bool (*CompareStrings)(const std::string&, const std::string&);
	typedef bool (*ComparePages)(const PageNumber first_page, const PageNumber second_page);
	typedef bool (*Compare)(const ListElement&, const ListElement&);

private:

	

public:

	void Add(const std::string& termin_name, PageNumber page_number) {

		ListElement list_element;

		list_element.name = termin_name;
		list_element.under_term_list_ptr = (TerminsList*) new TerminsList();
		list_element.page_list_ptr = (lst::forward_list<PageNumber>*) new lst::forward_list<PageNumber>();
		list_element.page_list_ptr->push_back(page_number);

		push_back(list_element);

	}

	void Delete(const std::string& delete_termin_name) {

		if (!empty()) {

			unsigned int index = 0;

			std::string current_termin_name;
			bool termin_found;

			do {

				const ListElement& list_element = operator[](index);
				current_termin_name = list_element.name;

				index++;

				termin_found = (current_termin_name == delete_termin_name) && (index < size());

			} while (!termin_found);

			index--;
			erase(index);

		}

	}

	void SortTerminsNames() {

		sort(CompareNames);

	}


	explicit TerminsList():lst::forward_list<ListElement>() {

	}

};

#endif