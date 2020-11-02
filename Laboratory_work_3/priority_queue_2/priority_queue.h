#pragma once
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "forward_list.h"
#include "QueueList.h"
#include "PriorityQueueException.h"



template<class DataType>
class priority_queue final:protected lst::forward_list<QueueList<DataType>>{
using Queue = QueueList<DataType>;
using List = lst::forward_list<Queue>;

private:

	bool index_is_correct(const size_t index)const noexcept;

protected:
public:

	explicit priority_queue()noexcept :
		List{} {}

	explicit priority_queue(const std::initializer_list<DataType>& init_list, const Priority priority)noexcept{
	
		for (const auto& obj : init_list) push(obj, priority);

	}

	bool empty()const noexcept;
	void push(const DataType& data, const Priority priority)noexcept;
	void push(const std::initializer_list<DataType>& init_list, const Priority priority)noexcept;
	DataType pop()throw(PriorityQueueException);
	DataType pop(const Priority priority)throw(PriorityQueueException);
	size_t elements_number(const Priority priority)const noexcept;
	size_t low_priority()const noexcept;
	size_t size()const noexcept;
	DataType& operator()(const size_t priority, const size_t index);

};

#endif


template<class DataType>
bool priority_queue<DataType>::index_is_correct(const size_t index)const noexcept {

	if (index > size() - 1) return false;
	return true;

}

template<class DataType>
bool priority_queue<DataType>::empty() const noexcept
{

	for (size_t index = 0; index < List::size(); index++)
		if (!List::operator[](index).empty()) return false;

	return true;
}

template<class DataType>
void priority_queue<DataType>::push(const DataType& data, const Priority priority) noexcept{

	bool list_end = List::empty();
	bool queue_found = false;
	const size_t list_size = List::size();
	size_t index = 0;

	while (!list_end && !queue_found) {

		if (List::operator[](index).get_priority() == priority)
			queue_found = true;

		index++;

		if (index == list_size)
			list_end = true;

	}

	index--;

	if (queue_found) 
		List::operator[](index).push(data);
	else 
		List::push_back(Queue{ priority, data });

}

template<class DataType>
inline void priority_queue<DataType>::push(const std::initializer_list<DataType>& init_list, const Priority priority) noexcept
{

	for (const auto& obj : init_list) push(obj, priority);

}

template<class DataType>
DataType priority_queue<DataType>::pop()throw(PriorityQueueException)
{
	if (priority_queue::empty())throw PriorityQueueException("Priority queue is empty.");

	for (size_t index = 0; index < List::size(); index++){

		Queue& queue_list = List::operator[](index);

		if (!queue_list.empty())
			return queue_list.pop();

	}

	throw PriorityQueueException("Priority queue is empty.");
	
}

template<class DataType>
DataType priority_queue<DataType>::pop(const Priority priority)throw(PriorityQueueException)
{
	if (List::empty())throw PriorityQueueException("Not found such element.");

	for (size_t index = 0; index < List::size(); index++){
		
		Queue& queue_list = List::operator[](index);

		if (queue_list.get_priority() == priority) {

			if (!queue_list.empty()) 
				return queue_list.pop();
			else
				throw PriorityQueueException("Not found such element.");

		}
	}

}

template<class DataType>
size_t priority_queue<DataType>::elements_number(const Priority priority) const noexcept
{
	for (size_t index = 0; index < List::size(); index++){

		if (List::operator[](index).get_priority() == priority)return List::operator[](index).size();

	}

	return 0;
}

template<class DataType>
size_t priority_queue<DataType>::low_priority() const noexcept{


	return List::size();
}

template<class DataType>
size_t priority_queue<DataType>::size() const noexcept{
	size_t queue_size = 0;

	for (size_t index = 0; index < List::size(); index++)
		queue_size += List::operator[](index).size();

	return queue_size;
}

template<class DataType>
inline DataType& priority_queue<DataType>::operator()(const size_t priority, const size_t index)throw(PriorityQueueException){
	
	try {

		for (size_t i = 0; i < List::size(); i++) {

			Queue& queue_list = List::operator[](i);

			if (queue_list.get_priority() == priority && !queue_list.empty()) {

				return queue_list[index];

			}

		}

		throw PriorityQueueException("No such element.");
	}
	catch (lst::base_list::ListException exception) {

		throw PriorityQueueException(exception.GetError());

	}

}

