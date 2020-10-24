#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include"forward_list.h"
#include"PriorityQueueException.h"

namespace tl {

	using Priority = unsigned int;



	template<class ElementType>
	class priority_queue final {
	public:

		class QueueElement final {
		public:

			Priority priority_ = 0;
			ElementType data_;

			explicit QueueElement(const Priority priority, const ElementType& data)noexcept :priority_(priority), data_(data) {};
			explicit QueueElement()noexcept : data_() {};
			QueueElement& operator= (const QueueElement& element)noexcept {

				priority_ = element.priority_;
				data_ = element.data_;
				return *this;
			}
		};

	private:

		lst::forward_list<QueueElement> list_;

	protected:
	public:

		

		explicit priority_queue()noexcept :list_() {}
		inline size_t size()const noexcept { return list_.size(); };
		void insert(const ElementType& new_element, const Priority priority)noexcept {

			int index = -1;
			const size_t queue_size = list_.size();
			bool position_found = false;
			bool end_of_queue = list_.empty();

			while (!position_found && !end_of_queue) {
				
				index++;
				position_found = (list_[index ].priority_ > priority);
				end_of_queue = (index  == queue_size - 1);

			}

			if (position_found) 
				list_.insert(index - 1, QueueElement{ priority, new_element });
			else 
				list_.push_back(QueueElement{ priority, new_element });

		}

		QueueElement get(const size_t priority)throw(PriorityQueueException) {

			if (list_.empty()) throw PriorityQueueException("Priority queue is empty.");

			bool element_found = false;
			size_t index = 0;

			while (!element_found) {

				element_found = (list_[index].priority_ == priority);
				index++;

			}

			index--;

			QueueElement element = list_[index];
			list_.erase(index);

			return element;

		}

		QueueElement get()throw(PriorityQueueException) { 
			
			if (list_.empty())throw PriorityQueueException("Priority queue is empty.");
			return list_.pop_front();

		}

		QueueElement& operator[](const size_t index) {

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