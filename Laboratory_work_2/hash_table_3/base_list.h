#pragma once
#ifndef _BASE_LIST_H_
#define _BASE_LIST_H_

#include <string>

const int MAX = 100;

using std::string;

class ListException {
private:

	string method_name_;

public:

	inline string GetError()const noexcept { return method_name_; };

	explicit ListException(string method_name)noexcept :method_name_(method_name) {}

};

class base_list {

protected:

	unsigned int number_of_elements;

	inline bool indexIsCorrect(const unsigned int index) const noexcept {
		return (index >= 0) && (index < number_of_elements) && ((index + 1) <= MAX);
	}

private:


public:

	
	explicit base_list()noexcept : number_of_elements(0){};

	inline unsigned int size() const noexcept { return number_of_elements; };
	inline bool empty()const noexcept { return ( number_of_elements == 0 ); };
	inline int max_size()const noexcept { return MAX; }

};

#endif