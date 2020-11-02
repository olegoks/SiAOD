#pragma once
#ifndef _QUEUELIST_H_
#define _QUEUELIST_H_

#include "forward_list.h"

using Priority = unsigned int;

template<class DataType>
class QueueList final:public lst::forward_list<DataType> {

	using List = lst::forward_list<DataType>;

private:

	Priority priority_;

protected:
public:

	explicit QueueList(const Priority priority)noexcept :
		List{},
		priority_{ priority }
		{}

	explicit QueueList()noexcept :
		QueueList{ 0 } {}

	QueueList(const QueueList& queue_list)noexcept :
		List{ queue_list },
		priority_{ queue_list.priority_ } {}

	explicit QueueList(QueueList&& queue_list)noexcept:
		List{ queue_list.list_ }{
	
		std::swap(priority_, queue_list.priority_);

	}
	
	explicit QueueList(const Priority priority, const DataType& data)noexcept:
		QueueList{ priority } {

		push(data);

	}

	inline bool empty()const noexcept { return List::empty(); }
	inline void push(const DataType& data)noexcept { List::push_back(data); }
	inline DataType pop()noexcept { return List::pop_front(); }
	inline Priority get_priority()const noexcept { return priority_; };
	inline size_t size()const noexcept { return List::size(); }

	inline DataType& operator[](const size_t index)throw(lst::base_list::ListException) {

		return List::operator[](index);

	}

	inline void operator=(const QueueList& queue_list)noexcept {

		List::operator=(queue_list);
		priority_ = queue_list.priority_;

	}

	inline void operator=(QueueList&& queue_list)noexcept {

		List::operator=(std::move(queue_list));
		std::swap(priority_, queue_list.priority_);

	}

};

#endif