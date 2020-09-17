#pragma once
#ifndef _RING_LIST_H_
#define _RING_LIST_H_

class ring_list {

	typedef unsigned int uint;
	struct Element{
		uint index;
		Element* next;
		Element(uint index_, Element* next_) :index(index_), next(next_) {

		}
	};

private:

	Element* head_;

public:

	void create(const uint number_of_elements) {

		Element* ptr = head_;

		for (uint i = 0; i < number_of_elements; i++) {

			ptr->next = new Element(i + 1, nullptr);
			ptr = ptr->next;


		}
	
		ptr->next = head_->next;

	}

	void clear() {



	}

};
#endif