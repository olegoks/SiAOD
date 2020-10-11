#pragma once
#ifndef _TERMBASE_H_
#define _TERMBASE_H_

#include <string>
#include "multimap.h"
#include <iostream>

using PageNumber = unsigned int;
static const unsigned int DEFAULT_MAP_SIZE = 10;
static const PageNumber DEFAULT_PAGE_NUMBER = 0;
static std::string DEFAULT_TERMIN_NAME = "Default.";

class TermName :public std::string {
public:

	inline operator mp::KeyValue()const { return operator[](0); }
	TermName(std::string str) :std::string(str) {

	}

	TermName():std::string() {

	}

};


class Termin{


private:

	TermName over_term_, term_, under_term_;
	PageNumber page_;

protected:

public:

	explicit Termin(const TermName over_term_name, const TermName term_name, const TermName under_term_name, const PageNumber page_number)noexcept;
	explicit Termin()noexcept;
	inline TermName GetName()const noexcept{ return term_; }
	inline void SetUnderTermName(TermName name) { under_term_ = name; }
	inline void SetTermName(TermName name) { term_ = name; }
	inline void SetOverTermName(TermName name) { over_term_ = name; }
	
};



class SubjectIndex {

	using Map = mp::map<TermName, Termin>;
	using uint = unsigned int;

private:
	
	std::vector<Map*> levels_;

protected:
public:

	explicit SubjectIndex(const uint depth)noexcept;

	void Add(Termin termin, Termin under_termin, Termin under_under_termin);
	void Add(Termin termin, Termin under_termin);
	void Add(Termin termin);



};


#endif