#pragma once
#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "base_list.h"
#include "abstract_list.h"

namespace nmspc {

	template<class DataType>
	class double_linked_list :public base_list, public abstract_list<DataType>
	{
		struct Element {

			DataType data;
			Element* next;
			Element* previous;

		};

	private:

		Element* const head_;
		
	public:

		void insert(const unsigned int index, const DataType& new_data)override;
		void erase(const unsigned int index)override;
		void push_back(const DataType& new_data)override;
		DataType& operator[](const int index)override;
		DataType pop_back()override;

		explicit double_linked_list():base_list(), head_((Element*) new Element()) {

		}

	};

	template<class DataType>
	inline void double_linked_list<DataType>::insert(const unsigned int index, const DataType& new_data)
	{
	}

	template<class DataType>
	inline void double_linked_list<DataType>::erase(const unsigned int index)
	{
	}

	template<class DataType>
	inline void double_linked_list<DataType>::push_back(const DataType& new_data)
	{
	}

	template<class DataType>
	inline DataType& double_linked_list<DataType>::operator[](const int index)
	{
		// TODO: вставьте здесь оператор return
	}

	template<class DataType>
	inline DataType double_linked_list<DataType>::pop_back()
	{
		return DataType();
	}

}
#endif 
