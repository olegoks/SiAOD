#include "TerminsList.h"
#include <iostream>

bool CompareNames(const Termin& first_element, const Termin& second_element) {

	return first_element.GetName() > second_element.GetName();

}

bool ComparePages(const Termin& first_termin, const Termin& second_termin) {

	const size_t FIRST_PAGE = 0;
	const size_t SECOND_PAGE = 0;

	try {

		const PageNumber first_page = first_termin.GetPage(FIRST_PAGE);
		const PageNumber second_page = second_termin.GetPage(SECOND_PAGE);

		return first_page > second_page;
	}
	catch (TerminException exception) {

		throw TerminsListException(exception.What());

	}

}

Termin& TerminsList::operator[](const size_t index) {

	try {

		return forward_list::operator[](index);

	}
	catch (ForwardListException exception) {

		throw TerminsListException(exception.GetError());

	}

}

void TerminsList::Add(const std::string& termin_name, PageNumber page_number)
{

	try {

		const Termin new_termin(termin_name, page_number);
		push_back(new_termin);

	}
	catch (ForwardListException exception) {

		throw TerminsListException(exception.GetError());

	}

}

void TerminsList::Delete(const std::string& delete_termin_name) {

	if (empty()) throw TerminsListException(LIST_IS_EMPTY);

	size_t index = 0;
	std::string current_termin_name;
	bool termin_found = false, end = false;

	do {

		const Termin& current_termin = operator[](index);
		current_termin_name = current_termin.GetName();

		termin_found = (current_termin_name == delete_termin_name);
		index++;
		end = index >= size();
		
	} while (!termin_found && !end);

	if (termin_found) erase(--index);
	else 
		throw TerminsListException(TERMIN_NOT_FOUND);

}

static const std::string DEFAULR_TERM_NAME = "Default.";
static const PageNumber DEFAULT_PAGE_NUMBER = 0;

Termin::Termin()noexcept :Termin(DEFAULR_TERM_NAME, DEFAULT_PAGE_NUMBER) {

}

// Оператор присваивания перемещением, который передает право собственности на x.m_ptr в m_ptr
Termin& Termin::operator=(Termin&& x)noexcept
{
	std::swap(this->name_, x.name_);
	std::swap(this->page_list_ptr_, x.page_list_ptr_);
	std::swap(this->under_term_list_ptr_, x.under_term_list_ptr_);

	return *this;
}
Termin::Termin(Termin&& time_object) noexcept
{
	name_= time_object.name_;
	//std::swap(time_object.name_, name_);
	std::swap(time_object.page_list_ptr_, page_list_ptr_);
	std::swap(time_object.under_term_list_ptr_, under_term_list_ptr_);

}

Termin::Termin(const Termin& time_object) noexcept
{

	this->name_ = time_object.name_;
	this->page_list_ptr_ = time_object.page_list_ptr_;
	this->under_term_list_ptr_ = time_object.under_term_list_ptr_;

}

Termin& Termin::operator=( const Termin& termin) noexcept
{

	this->name_ = termin.name_;
	this->page_list_ptr_ = termin.page_list_ptr_;
	this->under_term_list_ptr_ = termin.under_term_list_ptr_;

	return *this;
}

Termin::Termin(const string& _name, const PageNumber page_number)noexcept :

	name_(_name),
	under_term_list_ptr_(nullptr),
	page_list_ptr_((PagesList*) new PagesList){
	page_list_ptr_->push_back(page_number);

}

TerminsList& Termin::GetUnderTerminsList() const
{

	if (under_term_list_ptr_ != nullptr) {

		return *under_term_list_ptr_;
		
	}
	else {

		throw TerminException("Under termin list is empty.");

	}

}

PageNumber Termin::GetPage(const unsigned int page_index)const
{
	try {

		PageNumber page = (*page_list_ptr_)[page_index];

		return page;

	}
	catch (ForwardListException exception) {

		throw TerminException("No such page.");

	}

}

void Termin::AddUnderTermin(const Termin& under_termin)
{
	try {

		if (under_term_list_ptr_ == nullptr)under_term_list_ptr_ = (TerminsList*) new TerminsList;
		(*under_term_list_ptr_).Add(under_termin.GetName(), under_termin.GetPage(0));

	}
	catch (TerminsListException exception) {

		throw TerminException(exception.What());

	}

}

void Termin::AddUnderTermin(const std::string& under_termin_name, const PageNumber page_number)
{
	try {

		if (under_term_list_ptr_ == nullptr)under_term_list_ptr_ = (TerminsList*) new TerminsList;
		(*under_term_list_ptr_).Add(under_termin_name, page_number);

	}
	catch (TerminsListException exception) {

		throw TerminException(exception.What());

	}

}

void Termin::DeleteUnderTermin(const std::string& under_termin_name)
{
	try {

		(*under_term_list_ptr_).Delete(under_termin_name);

	}
	catch (TerminsListException exception) {

		throw TerminException(exception.What());

	}

}

void Termin::Edit(const string& new_name)
{
	
	name_ = new_name;

}

void Termin::Edit(const string& new_name, const PageNumber new_page)
{

	name_ = new_name;

	try {

		(*page_list_ptr_)[0] = new_page;

	}
	catch (ForwardListException exception) {

		(*page_list_ptr_).push_back(new_page);

	}

}

void Termin::Edit(const PageNumber new_page)
{

	try {

		(*page_list_ptr_)[0] = new_page;

	}
	catch (ForwardListException exception) {

		(*page_list_ptr_).push_back(new_page);

	}

}

const std::string Termin::GetPrintString() const
{

	return (name_ + ", " + std::to_string(GetPage(0)));

}