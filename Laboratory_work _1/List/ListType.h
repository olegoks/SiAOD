#pragma once
#ifndef _LIST_H_
#define _LIST_H_

namespace nmspc {

	const unsigned int MAX = 100;

	template<class DataType>
	class abstract_list {

	protected:

		unsigned int number_of_elements;

		inline bool indexIsCorrect(const unsigned int index) const noexcept {
			return (index >= 0) && (index < number_of_elements) && ((index + 1) < MAX);
		}

	private:


	public:
		
		void push_back(const DataType& new_data);
		void erase(const unsigned int index);
		void insert(const unsigned int index, const DataType& new_data);
		DataType& operator[](const int index);

		abstract_list()noexcept: number_of_elements(0) {};
		inline unsigned int size()  const noexcept  { return number_of_elements; };

		class ListException {
		private:

			const char* method_name_;

		public:

			inline const char* GetError()const noexcept { return method_name_; };
			explicit ListException(const char* method_name)noexcept :method_name_(method_name) {}

		};

	};


	template<class DataType>
	class forward_list:public abstract_list<DataType>{

		struct Element {

			DataType data;
			Element* next;
			explicit Element(DataType data_) noexcept :data(data_), next(nullptr) {}
			explicit Element()noexcept : data(), next(nullptr) {}
		};

	private:

		Element* head_;

	public:



		void insert(const unsigned int index, const DataType& new_data);
		void erase(const unsigned int index);
		void push_back(const DataType& new_data);
		DataType& operator[](const int index);

		explicit forward_list()noexcept:abstract_list(){ head_ = (Element*) new Element(); }
		~forward_list();



	};



	template<class DataType>
	void forward_list<DataType>::insert(const unsigned int index, const DataType& new_data)
	{

		if (!abstract_list<DataType>::indexIsCorrect(index)) throw abstract_list<DataType>::ListException("Exception in the method insert.");

		Element* first_ptr = head_->next;
		for (size_t i = 0; i < (index - 1); i++) first_ptr = first_ptr->next;
		Element* second_ptr = first_ptr;
		first_ptr = first_ptr->next;
		Element* new_element = (Element*) new Element();
		new_element->data = new_data;
		new_element->next = first_ptr;
		second_ptr->next = new_element;
		++abstract_list<DataType>::number_of_elements;

	}

	template<class DataType>
	void nmspc::forward_list <DataType>::erase(const unsigned int index)
	{

		if (!abstract_list<DataType>::indexIsCorrect(index))throw abstract_list<DataType>::ListException("Exception in the method erase.");

		Element* first_ptr = head_->next;
		for (size_t i = 0; i < (index - 1); i++) first_ptr = first_ptr->next;
		Element* second_ptr = first_ptr;
		first_ptr = (first_ptr->next)->next;
		delete second_ptr->next;
		second_ptr->next = first_ptr;
		--abstract_list<DataType>::number_of_elements;

	}

	template<class DataType>
	void forward_list <DataType>::push_back(const DataType& new_data)
	{	
		if (abstract_list<DataType>::number_of_elements >= MAX) throw abstract_list<DataType>::ListException("Exception in the method push_back.");

		Element* ptr = head_;
		for (size_t i = 0; i < abstract_list<DataType>::number_of_elements; i++) ptr = ptr->next;
		Element* const new_element = (Element*) new Element(new_data);
		ptr->next = new_element;
		++abstract_list<DataType>::number_of_elements;

	}

	template<class DataType>
	forward_list<DataType>::~forward_list()
	{
		{

			Element* ptr_next, * ptr_this = head_;

			for (size_t i = 0; i < abstract_list<DataType>::number_of_elements; i++)
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

		if (!abstract_list<DataType>::indexIsCorrect(index)) throw abstract_list<DataType>::ListException("Exception in the method operator[].");

		Element* ptr = head_->next;

		for (int i = 0; i < index; i++) ptr = ptr->next;

		return ptr->data;

	}
}

#endif


