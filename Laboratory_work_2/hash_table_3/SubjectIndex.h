#pragma once
#ifndef _TERMBASE_H_
#define _TERMBASE_H_

#include <vector>
#include <iostream>
#include "TerminsList.h"
#include "multimap.h"
#include "SubjectIndexException.h"

const static string NO_UNDERTERMIN = "No undertermin.";

static class TerminName :public string {
private:

protected:

public:

	explicit TerminName(const string& name)noexcept:string(name) {	}
	explicit TerminName()noexcept:string(){ }
	inline operator int()const noexcept { return operator[](0); }
	
};
	
using TerminsInfo = std::vector<const Termin*>;

class SubjectIndex {

private:

	TerminsInfo termins_info_;
	mp::map<TerminName, Termin> termins_;

protected:

public:

	void AddTermin(const string& name, const PageNumber page_number);
	void AddUnderTermin(const string& termin_name, const string& under_termin_name, const PageNumber page_number);
	void AddUnderUnderTermin(const string& termin_name, const string& under_termin_name, const string& under_under_termin_name, const PageNumber page_number);
	void Print()const;
	void SortTerminsNames();
	void SortPages();
	void EditTermin(const string& termin_name, const string& new_name, const PageNumber new_page);
	void DeleteTermin(const string& delete_termin_name);
	void DeleteUnderTermin(const string& delete_termin_name, const string& delete_under_termin_name);
	Termin SearchTermin(const string& termin_name)const;
	explicit SubjectIndex()noexcept;

};
#endif