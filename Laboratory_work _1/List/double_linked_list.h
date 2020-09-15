#pragma once
#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include "base_list.h"
#include "abstract_list.h"

namespace lst {

	template<class DataType>
	class double_linked_list :public base_list, public abstract_list<DataType>
	{
		struct Element {

			DataType data;
			Element* next;
			Element* previous;

			explicit Element(DataType data_) noexcept :data(data_), next(nullptr), previous(nullptr) {}
			explicit Element()noexcept : data(), next(nullptr), previous(nullptr) {}

		};

	private:

		Element* const head_;
		Element* ass_;
		
	public:

		void insert(const int index, const DataType& new_data)override;
		void erase(const int index)override;
		void push_back(const DataType& new_data)override;
		DataType& operator[](const int index)override;
		DataType pop_back()override;
		DataType pop_front()override;

		explicit double_linked_list():base_list(), head_((Element*) new Element()) {
			ass_ = head_;
		}

	};

	template<class DataType>
	inline void double_linked_list<DataType>::insert(const int index, const DataType& new_data)
	{

		if (!indexIsCorrect(index)) throw ListException("Exception in the method insert.");
		if (index == ( number_of_elements - 1) ) { this->push_back(new_data); }
		else
		{
			Element* first_ptr = head_->next;
			for (int i = 0; i < (index - 1); i++) first_ptr = first_ptr->next;
			Element* second_ptr = first_ptr;
			first_ptr = first_ptr->next;
			Element* const new_element = (Element*) new Element();
			second_ptr->next = new_element;
			new_element->previous = second_ptr;
			new_element->next = first_ptr;
			first_ptr->previous = new_element;
			new_element->data = new_data;
			++number_of_elements;

		}

	}

	template<class DataType>
	inline void double_linked_list<DataType>::erase(const int index)
	{

		if (!indexIsCorrect(index))throw ListException("Exception in the method erase.");

		if (index == (number_of_elements - 1)) this->pop_back();
		else
			if (index == 0)this->pop_front(); 
			else {

				Element* first_ptr = head_->next;
				for (int i = 0; i < (index - 1); i++) first_ptr = first_ptr->next;
				Element* second_ptr = first_ptr;
				first_ptr = (first_ptr->next)->next;
				delete second_ptr->next;
				second_ptr->next = first_ptr;
				first_ptr->previous = second_ptr;

				--number_of_elements;
			}
	}

	template<class DataType>
	inline void double_linked_list<DataType>::push_back(const DataType& new_data)
	{

		if (number_of_elements >= MAX) throw ListException("Exception in the method push_back.");

		Element* ptr = head_;
		for (size_t i = 0; i < number_of_elements; i++) ptr = ptr->next;
		Element* const new_element = (Element*) new Element(new_data);
		ptr->next = new_element;
		new_element->previous = ptr;
		ass_ = new_element;


		++number_of_elements;

	}

	template<class DataType>
	inline DataType double_linked_list<DataType>::pop_front() {

		if ( number_of_elements == 0 )throw ListException("Exception int the method pop_front.");

		Element* pop_element = head_->next;

		if (pop_element->next != nullptr) {

			head_->next = pop_element->next;
			(pop_element->next)->next = head_;

		}
		else
			head_->next = nullptr;

		delete pop_element;

		--number_of_elements;

	}

	template<class DataType>
	inline DataType& double_linked_list<DataType>::operator[](const int index)
	{
		if (!indexIsCorrect(index)) throw ListException("Exception in the method operator[].");

		Element* ptr_head = head_->next;
		Element* ptr_ass = ass_;
		int middle = number_of_elements;

		if (middle < index) {
			for (int i = 0; i < index; i++) ptr_head = ptr_head->next;
			return ptr_head->data;
		}
		else {
			for (int i = 0; i < number_of_elements - index - 1; i++) {
				ptr_ass = ptr_ass->previous;
			}
			return ptr_ass->data;
		}
				

	}

	template<class DataType>
	inline DataType double_linked_list<DataType>::pop_back()
	{
		if (number_of_elements == 0) throw ListException("Exception in the method insert.");

		Element* ptr = head_;
		for (size_t i = 0; i < (number_of_elements - 1); i++)ptr = ptr->next;
		DataType data;
		data = (ptr->next)->data;
		delete ptr->next;
		ptr->next = nullptr;
		--number_of_elements;

		return DataType();
	}

}
#endif 
