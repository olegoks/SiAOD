#pragma once
#ifndef _TERMINS_LIST_H_
#define _TERMINS_LIST_H_

#include "forward_list.h"
#include <string>
#include "TerminsListException.h"
#include "TerminException.h"

using PageNumber = unsigned int;
using PagesList = forward_list<PageNumber>;

class TerminsList;

class Termin {

private:

	string name_;
	TerminsList* under_term_list_ptr_;
	PagesList* page_list_ptr_;

protected:

public:

	explicit Termin()noexcept;
	explicit Termin(const string& _name, const PageNumber page_number)noexcept;
	inline const string& GetName()const noexcept { return name_; }
	TerminsList& GetUnderTerminsList()const;
	inline PageNumber GetNumberOfPages()const noexcept { return page_list_ptr_->size(); }
	PageNumber GetPage(const unsigned int page_index)const;
	void AddUnderTermin(const Termin& under_termin);
	void AddUnderTermin(const string& under_termin_name, const PageNumber page_number);
	void DeleteUnderTermin(const string& under_termin_name);
	void Edit(const string& new_name);
	void Edit(const string& new_name, const PageNumber new_page);
	void Edit(const PageNumber new_page);
	const string GetPrintString() const;
	Termin& operator=(Termin&& x)noexcept;
	Termin(Termin&& time_object)noexcept;
	Termin(const Termin& time_object)noexcept;
	Termin& operator=(const Termin& termin)noexcept;

};

static const string LIST_IS_EMPTY = "Termins list is empty.";
static const string TERMIN_NOT_FOUND = "Termin not found.";

class TerminsList:protected forward_list<Termin> {
private:
public:

	//const Termin& operator[](const size_t index)const;
	Termin& operator[](const size_t index);
	void Add(const string& termin_name, PageNumber page_number);
	void Delete(const string& delete_termin_name);
	inline void SortTerminsNames() { /*sort(CompareNames);*/ }
	inline void SortPages() { /*sort(ComparePages);*/ }
	inline size_t GetNumberOfTermins()const noexcept { return size(); }
	explicit TerminsList()noexcept:forward_list<Termin>() {}

};

#endif