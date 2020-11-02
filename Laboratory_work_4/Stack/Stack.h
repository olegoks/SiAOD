#pragma once
#include "forward_list.h"
template<class DataType>
class Stack final: private lst::forward_list<DataType>
{

	using ForwardList = lst::forward_list<DataType>;

private:
protected:
public:

	void push(const DataType& data)noexcept;
	DataType&& pop();
	inline size_t size()const noexcept(true);
	explicit Stack()noexcept(true);
};

template<class DataType>
DataType&& Stack<DataType>::pop()noexcept(false) {

	return ForwardList::pop_front();

}

template<class DataType>
inline size_t Stack<DataType>::size() const noexcept(true){
	
	return lst::forward_list<DataType>::size();

}

template<class DataType>
inline Stack<DataType>::Stack() noexcept(true):
	ForwardList{} {

}

template<class DataType>
void Stack<DataType>::push(const DataType& data) noexcept{

	ForwardList::push_front(data);

}
