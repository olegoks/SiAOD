#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include"forward_list.h"
#include"PriorityQueueException.h"

namespace tl {

	template<class ElementType>
	class priority_queue final {

		using Priority = unsigned int;

		class queue_element final {
		public:

			Priority priority_ = 0;
			ElementType data_;

			explicit queue_element(const Priority priority, const ElementType& data)noexcept :priority_(priority), data_(data) {};
			explicit queue_element()noexcept : data_() {};

		};

	private:

		lst::forward_list<queue_element> list_;

	protected:
	public:

		explicit priority_queue()noexcept :list_() {}

		void add(const ElementType& new_element, const Priority priority)noexcept {

			size_t index = 0;
			const size_t queue_size = list_.size();
			bool position_found = false, end_of_queue = (queue_size == 0);

			while (!position_found && !end_of_queue) {

				position_found = (list_[index].priority_ > priority);
				index++;
				end_of_queue = index >= queue_size;

			}

			if (list_.empty()) {

				list_.push_back(queue_element{ priority, new_element });
			}
			else {

				list_.insert(index -1 , queue_element{ priority, new_element });

			}

		}

		ElementType get(const size_t priority)throw(PriorityQueueException) {

			if (list_.empty()) throw PriorityQueueException("Priority queue is empty.");

			bool element_found = false;
			size_t index = 0;

			while (!element_found) {

				element_found = (list_[index].priority == priority);

			}

			ElementType element = list_[index];
			list_.erase(index);

			return element;

		}

		ElementType get()throw(PriorityQueueException) { 
			
			if (list_.empty())throw PriorityQueueException("Priority queue is empty.");
			return list_.pop_front();

		}

		ElementType& operator[](const size_t index)throw(PriorityQueueException) {

			try {
				return list_[index];
			}
			catch (lst::base_list::ListException exception) {

				throw PriorityQueueException(exception.GetError());

			}

		}




	};

};
#endif