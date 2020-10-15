#pragma once
#ifndef _TERMBASE_H_
#define _TERMBASE_H_
#include <string>
#include <iostream>
#include "TerminsList.h"

namespace ndx {

	using UnderTerminsList = lst::forward_list<ListElement>;

	struct Termin {

		std::string name;
		PageNumber page;
		const UnderTerminsList* under_termins;

	};

	class SubjectIndexException {
	private:

		const char* const error_name_;

	public:

		explicit SubjectIndexException(const char* const error_name)noexcept :
			error_name_(error_name) {

		}

		inline const char* What()const noexcept { return error_name_; }
	};

	class SubjectIndex {
	private:

		TerminsList list_;

	protected:

	public:

		void AddTermin(const std::string& name, const PageNumber page_number);
		void AddUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const PageNumber page_number);
		void AddUnderUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const std::string& under_under_termin_name, const PageNumber page_number);
		void Print()const;
		void SortTerminsNames();
		void EditTermin(const std::string& termin_name, const std::string& new_name, const PageNumber new_page);
		void DeleteTermin(const std::string& delete_termin_name);
		void DeleteUnderTermin(const std::string& delete_termin_name, const std::string& delete_under_termin_name);
		Termin SearchTermin(const std::string& termin_name)const;
		explicit SubjectIndex()noexcept;

	};

}
#endif