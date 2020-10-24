#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
namespace tl {

#include"forward_list.h"



template<class ElementType>
class priority_queue final{

	using Priority = unsigned int;

	class queue_element final {
	public:

		Priority priority_ = 0;
		ElementType data_;

	};

private:

	lst::forward_list<queue_element> list_;

protected:
public:

	explicit priority_queue()noexcept:list_(){}

	void add(const ElementType& new_element, const Priority priority) {

		size_t index = 0;
		const size_t queue_size = list_.size();
		bool position_found = false, end_of_queue = false;

		while (!position_found && !end_of_queue) {

			position_found = (list_[index].priority > priority);
			index++;
			end_of_queue = index >= queue_size;

		}

		list_.insert(index - 1, new_element);
		
	}

	ElementType get(const size_t priority) {

		bool element_found = false;
		size_t index = 0;

		while (!element_found) {

			element_found = (list_[index].priority == priority);

		}

		ElementType element = list_[index];
		list_.erase(index);

		return element;

	}

	ElementType get() {

		ElementType element = list_.pop_front();

		return element;

	}

	ElementType& operator[](const size_t index) {
		return list_[index];
	}


};

}
#endif