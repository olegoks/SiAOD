#pragma once
#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

#include "base_list.h"
#include "abstract_list.h"
#include "ForwardListException.h"

template<class DataType>
class forward_list:public base_list, abstract_list<DataType>{

	typedef bool (*CompareFunction)(const DataType&, const DataType&);

	struct Element {

		DataType data;
		Element* next;

		explicit Element(DataType data_) noexcept : data(data_), next(nullptr) { }
		explicit Element()noexcept :data(), next(nullptr) {}
		explicit Element(const Element& element)noexcept {

			data = element.data;
			next = element.next;

		}

		void operator= (Element& element) {

			data = element.data;
			next = element.next;

		}

	};

	private:

		Element* const head_;

	public:

		void swap(const unsigned int  first_index, const unsigned int second_index );
		void insert(const int index, const DataType& new_data)override;
		void erase(const int index)override;
		void push_back(const DataType& new_data)override;
		DataType& operator[](const int index)override;
		const DataType& operator[](const int index)const override;
		DataType pop_back()override;
		DataType pop_front()override;
		void sort(CompareFunction compare_function);


		explicit forward_list() :base_list(), head_((Element*) new Element()) {

		};

		~forward_list();

	};

	template<class DataType>
	DataType forward_list<DataType>::pop_front() {

		if (size() == 0) throw ListException("Exception in the method pop_front.");
		if (size() == 1) return pop_back();
		
		Element* ptr = head_->next->next;
		DataType data = head_->next->data;
		delete head_->next;
		head_->next = ptr;
		--number_of_elements;

		return data;
	}

	template<class DataType>
	inline void forward_list<DataType>::sort(CompareFunction compare_function){

		for (size_t i = 0; i < size(); i++) { 

			for (size_t j = size() - 1; j > i; j--) { 

				if ( compare_function((*this).operator[](j - 1), (*this).operator[](j)) ) {
					swap(j - 1, j);
				}

			}
		}
	}

	template<class DataType>
	DataType forward_list<DataType>::pop_back() {

		if (size() == 0) throw ListException("Exception in the method insert.");

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
	void forward_list<DataType>::swap(const unsigned int first_index, const unsigned int second_index) {

		const DataType temporary_data = operator[](first_index);
		operator[](first_index) = operator[](second_index);
		operator[](second_index) = temporary_data;

	}

	template<class DataType>
	void forward_list<DataType>::insert(const int index, const DataType& new_data){

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
	void forward_list <DataType>::erase(const int index){

		if (!indexIsCorrect(index))throw ListException("Exception in the method erase.");

		if (index == 0)this->pop_front();
		else 
			if (index == size() - 1)this->pop_back();
			else {

				Element* first_ptr = head_->next;
				for (size_t i = 0; i < index - 1; i++)first_ptr = first_ptr->next;
				Element* second_ptr = first_ptr;
				first_ptr = (first_ptr->next)->next;
				delete second_ptr->next;
				second_ptr->next = first_ptr;
				--number_of_elements;
				
			}

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

		Element* ptr_next, * ptr_this = head_;

		for (size_t i = 0; i < number_of_elements; i++)
		{

			ptr_next = ptr_this->next;
			delete ptr_this;
			ptr_this = ptr_next;

		}

		delete ptr_this;

	}

	template<class DataType>
	DataType& forward_list<DataType>::operator[](const int index){

		if (!indexIsCorrect(index)) throw ListException("Exception in the method operator[].");

		Element* ptr = head_->next;

		for (int i = 0; i < index; i++) ptr = ptr->next;

		return ptr->data;

	}

	template<class DataType>
	const DataType& forward_list<DataType>::operator[](const int index)const {

		if (!indexIsCorrect(index)) throw ListException("Exception in the method operator[].");

		Element* ptr = head_->next;

		for (int i = 0; i < index; i++) ptr = ptr->next;

		return ptr->data;

	}

#endif