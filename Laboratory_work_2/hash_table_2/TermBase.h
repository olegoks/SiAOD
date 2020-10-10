#pragma once
#ifndef _TERMBASE_H_
#define _TERMBASE_H_

#include <string>
#include "multimap.h"
#include <iostream>
using PageNumber = unsigned int;
static const unsigned int DEFAULT_MAP_SIZE = 10;
static const PageNumber DEFAULT_PAGE_NUMBER = 0;
static const char* DEFAULT_TERMIN_NAME = "Default.";

static class Termin{
private:

	std::string term_name_;
	const PageNumber page_number_;
	std::vector<std::string> under_terms_;

protected:

public:

	inline operator int()const { return term_name_[0]; }
	explicit Termin(const char* const_string, const PageNumber page_number)noexcept;
	explicit Termin()noexcept;

	//explicit Termin(Termin& termin)noexcept :{



	//}

	void operator= (Termin termin) {

	}

	~Termin() {

	}



};



class TermBase {
	using Map = mp::map<std::string, Termin>;
private:
	
	Map termins_, under_termins_, under_under_termins_;
	std::vector<std::string> termins_string_;

protected:
public:

	explicit TermBase()noexcept:
		termins_(DEFAULT_MAP_SIZE),
		under_termins_(DEFAULT_MAP_SIZE),
		under_under_termins_(DEFAULT_MAP_SIZE),
		termins_string_(){


	}

	void add() {



	}

	bool ReadTermsFile(const char* file_name);

};


#endif