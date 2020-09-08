#pragma once
#ifndef _ABSTRACT_LIST_H_
#define _ABSTRACT_LIST_H_

namespace nmspc {

	template<class DataType>
	class abstract_list {
	public:

		virtual void insert(const int index, const DataType& new_data) = 0;
		virtual void erase(const int index) = 0;
		virtual void push_back(const DataType& new_data) = 0;
		virtual DataType& operator[](const int index) = 0;
		virtual DataType pop_back() = 0;
		virtual DataType pop_front() = 0;

	};

}
#endif