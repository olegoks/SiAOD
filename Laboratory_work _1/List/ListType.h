#pragma once
#ifndef _LIST_H_
#define _LIST_H_

namespace nmspc {

	const unsigned int MAX = 100;

	template<class DataType>
	class List {

		struct Element {

			DataType data;
			Element* next;
			explicit Element(DataType data_) noexcept :data(data_), next(nullptr) {}
			explicit Element()noexcept : data(), next(nullptr) {}
		};

	private:

		unsigned int number_of_elements;
		Element* head_;

		inline bool indexIsCorrect(const unsigned int index)noexcept {

			return (index >= 0) && (index < number_of_elements) && ( ( index + 1 ) < MAX);
		}

	public:

		class ListException {
		private:

			const char* method_name_;

		public:

			inline const char* GetError()const noexcept { return method_name_; };
			explicit ListException(const char* method_name)noexcept :method_name_(method_name) {}
			
		};

		void insert(const unsigned int index, const DataType& new_data);
		void erase(const unsigned int index);
		void push_back(const DataType& new_data);
		inline unsigned int size()const noexcept { return number_of_elements; };
		explicit List() noexcept :number_of_elements(0) { head_ = (Element*) new Element(); }
		~List();
		DataType& operator[](const int index);


	};



	template<class DataType>
	void List<DataType>::insert(const unsigned int index, const DataType& new_data)
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
	void nmspc::List<DataType>::erase(const unsigned int index)
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
	void nmspc::List<DataType>::push_back(const DataType& new_data)
	{	
		if (number_of_elements >= MAX) throw ListException("Exception in the method push_back.");

		Element* ptr = head_;
		for (size_t i = 0; i < number_of_elements; i++) ptr = ptr->next;
		Element* const new_element = (Element*) new Element(new_data);
		ptr->next = new_element;
		++number_of_elements;

	}

	template<class DataType>
	List<DataType>::~List()
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
	DataType& List<DataType>::operator[](const int index) {

		if (!indexIsCorrect(index)) throw ListException("Exception in the method operator[].");

		Element* ptr = head_->next;

		for (size_t i = 0; i < index; i++) ptr = ptr->next;
		return ptr->data;

	}
}

#endif


