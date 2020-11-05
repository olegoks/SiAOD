#pragma once
#include "forward_list.h"
template<class DataType>
class Stack final: private lst::forward_list<DataType>
{

	using ForwardList = lst::forward_list<DataType>;

private:
protected:
public:

	void push(const DataType& data)noexcept(true);
	DataType&& pop()noexcept(false);
	const DataType& top()const noexcept(false);
	inline size_t size()const noexcept(true);
	inline bool empty()const noexcept(true);
	explicit Stack()noexcept(true);

};

template<class DataType>
DataType&& Stack<DataType>::pop()noexcept(false) {

	return ForwardList::pop_front();

}

template<class DataType>
inline size_t Stack<DataType>::size() const noexcept(true){
	
	return ForwardList::size();

}

template<class DataType>
inline bool Stack<DataType>::empty() const noexcept(true)
{
	return ForwardList::empty();
}

template<class DataType>
inline Stack<DataType>::Stack() noexcept(true):ForwardList{} {

}

template<class DataType>
void Stack<DataType>::push(const DataType& data) noexcept{

	ForwardList::push_front(data);

}

template<class DataType>
inline const DataType& Stack<DataType>::top()const noexcept(false) {

	if (!empty())
		return  this->operator[](0);
	
	throw lst::base_list::ListException("Stack is empty.");
	
}
