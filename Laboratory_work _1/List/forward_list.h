#pragma once
#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

#include "base_list.h"
#include "abstract_list.h"

namespace nmspc {

	template<class DataType>
	class forward_list : public base_list, abstract_list<DataType>{

		struct Element {

			DataType data;
			Element* next;
			explicit Element(DataType data_) noexcept :data(data_), next(nullptr) {}
			explicit Element()noexcept : data(), next(nullptr) {}

		};

	private:

		Element* const head_;

	public:

		void insert(const unsigned int index, const DataType& new_data)override;
		void erase(const unsigned int index)override;
		void push_back(const DataType& new_data)override;
		DataType& operator[](const int index)override;
		DataType pop_back()override;
	
		explicit forward_list() :base_list(), head_( (Element*) new Element() ) {

		};

		~forward_list();

	};

	template<class DataType>
	DataType forward_list<DataType>::pop_back() {

		if (number_of_elements == 0) throw ListException("Exception in the method insert.");

		Element* ptr = head_;
		for (size_t i = 0; i < (number_of_elements - 1); i++)ptr = ptr->next;
		DataType data;
		data = (ptr->next)->data;
		delete ptr->next;
		ptr->next = nullptr;
		--number_of_elements;

		return data;
	}

	template<class DataType>
	void forward_list<DataType>::insert(const unsigned int index, const DataType& new_data)
	{

		if (!indexIsCorrect(index)) throw ListException("Exception in the method insert.");

		Element* first_ptr = head_->next;
		for (size_t i = 0; i < (index - 1); i++) first_ptr = first_ptr->next;
		Element* second_ptr = first_ptr;
		first_ptr = first_ptr->next;
		Element* new_element = (Element*) new Element();
		new_element->data = new_data;
		new_element->next = first_ptr;
		second_ptr->next = new_element;
		++number_of_elements;

	}

	template<class DataType>
	void nmspc::forward_list <DataType>::erase(const unsigned int index)
	{

		if (!indexIsCorrect(index))throw ListException("Exception in the method erase.");

		Element* first_ptr = head_->next;
		for (size_t i = 0; i < (index - 1); i++) first_ptr = first_ptr->next;
		Element* second_ptr = first_ptr;
		first_ptr = (first_ptr->next)->next;
		delete second_ptr->next;
		second_ptr->next = first_ptr;
		--number_of_elements;

	}

	template<class DataType>
	void forward_list <DataType>::push_back(const DataType& new_data)
	{
		if (number_of_elements >= MAX) throw ListException("Exception in the method push_back.");

		Element* ptr = head_;
		for (size_t i = 0; i < number_of_elements; i++) ptr = ptr->next;
		Element* const new_element = (Element*) new Element(new_data);
		ptr->next = new_element;
		++number_of_elements;

	}

	template<class DataType>
	forward_list<DataType>::~forward_list()
	{

		{

			Element* ptr_next, * ptr_this = head_;

			for (size_t i = 0; i < number_of_elements; i++)
			{

				ptr_next = ptr_this->next;
				delete ptr_this;
				ptr_this = ptr_next;

			}

			delete ptr_this;

		}

	}

	template<class DataType>
	DataType& forward_list <DataType>::operator[](const int index) {

		if (!indexIsCorrect(index)) throw ListException("Exception in the method operator[].");

		Element* ptr = head_->next;

		for (int i = 0; i < index; i++) ptr = ptr->next;

		return ptr->data;

	}
}

#endif


