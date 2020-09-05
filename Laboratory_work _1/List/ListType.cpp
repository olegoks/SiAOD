#include "ListType.h"

template<class DataType>
void List<DataType>::Insert(const unsigned int index, DataType new_data)
{

	const bool index_is_correct = (index >= 0) && (index <= number_of_elements);

	if (!index_is_correct)throw ListException;

	Element* pointer = head_->next;

	for (size_t i = 0; i < index; i++) pointer = pointer->next;

	Element* new_element = (Element*) new Element;
	new_element->next = pointer;





}