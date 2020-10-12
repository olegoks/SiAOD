#pragma once
#ifndef _TERMBASE_H_
#define _TERMBASE_H_
#include <string>
#include <iostream>
#include "TerminsList.h"

namespace ndx {

	class SubjectIndex {

	private:

		TerminsList list_;

	protected:

	public:

		void AddTermin(const std::string& name, const PageNumber page_number);
		void AddUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const PageNumber page_number);
		void AddUnderUnderTermin(const std::string& termin_name, const std::string& under_termin_name, const std::string& under_under_termin_name, const PageNumber page_number);
		void Print()const;
		void DeleteTermin(const std::string& delete_termin_name);
		void DeleteUnderTermin(const std::string& delete_termin_name, const std::string& delete_under_termin_name);
		explicit SubjectIndex()noexcept;

	};

}
#endif