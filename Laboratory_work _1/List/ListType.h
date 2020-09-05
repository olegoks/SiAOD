#pragma once
#ifndef _LIST_H_
#define _LIST_H_


const unsigned int MAX = 100;

template<class DataType>
class List {

	struct Element {

		DataType data;
		Element* next;
		explicit Element(T data_) noexcept :data(data_), ptr(nullptr) {}
		explicit Element()noexcept : data(), ptr(nullptr) {}
	};

private:

	unsigned int number_of_elements;
	Element* head_;

public:

	class ListException {};

	void Insert(const unsigned int index, DataType new_data);

	explicit List() noexcept :number_of_elements(0) {

		head_ = (Element*) new Element();

	}



};
#endif


