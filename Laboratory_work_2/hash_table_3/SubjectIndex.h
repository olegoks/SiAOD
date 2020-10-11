#pragma once
#ifndef _TERMBASE_H_
#define _TERMBASE_H_
#include <string>
#include <iostream>
#include "forward_list.h"

namespace ndx {

	static const std::string DEFAULR_TERM_NAME = "Default.";

	class SubjectIndex {

		using uint = unsigned int;
		using PageNumber = uint;

		struct ListElement {

			std::string name;
			lst::forward_list<ListElement>* under_term_list_ptr;
			lst::forward_list<PageNumber>* page_list_ptr;

			ListElement()noexcept :
				name(DEFAULR_TERM_NAME),
				under_term_list_ptr(nullptr),
				page_list_ptr(nullptr)
			{

			}

			ListElement(const std::string& _name, const PageNumber page_number)noexcept :
				name(_name),
				under_term_list_ptr(nullptr),
				page_list_ptr(nullptr) {

			}


		};


	private:

		lst::forward_list<ListElement> list_;

	protected:

	public:

		void AddTermin(const std::string& name, const PageNumber page_number);
		void AddUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const PageNumber page_number);

		explicit SubjectIndex()noexcept;

	};

}
#endif