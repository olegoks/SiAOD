#pragma once
#ifndef _MULTIMAP_H_
#define _MULTIMAP_H_
#include <vector>
#include "forward_list.h"
#include "MapException.h"

namespace mp {

using KeyValue = int;

static const std::string LIST_IS_EMPTY = "List is empty.";
static const std::string TERMIN_NOT_FOUND = "Termin not found.";

template<class Key, class Value>
class map {

	struct ListElement {

		Key key;
		Value value;

		explicit ListElement()noexcept: key(), value() {

		}
		explicit ListElement(Key _key, Value _value)noexcept:key(_key),
		value(_value){

		}
	};

	using List = forward_list<ListElement>;
	using HashTable = std::vector<List*>;

	using Hash = unsigned int;
	using uint = unsigned int;

	private:

	HashTable table_;

	inline Hash ReturnHash(KeyValue key) const{

		return key % table_.size();

	}

	uint GetHash(const Key& key)const {

		KeyValue key_value = (KeyValue)key;
		const Hash hash = ReturnHash(key_value);

		return hash;

	}

	public:

	explicit map(const uint size)noexcept {

		for (uint i = 0; i < size; i++)
		{

			table_.push_back((List*) new List);

		}
				
	}

	Value& operator[](const Key& key) const {

		const Hash hash = GetHash(key);
		List* list_ptr = table_[hash];

		if (list_ptr->empty()) throw MapException(LIST_IS_EMPTY);

		size_t list_size = list_ptr->size();

		for (uint i = 0; i < list_size; i++)
		{

			ListElement& list_element = (*list_ptr)[i];
			const bool element_found = (list_element.key == key);

			if (element_found) return list_element.value;

		}

		throw MapException(TERMIN_NOT_FOUND);

	}

	void Add(const Key& key,const Value& value) {

		const Hash hash = GetHash(key);
		List* const list_ptr = table_[hash];

		list_ptr->push_back(ListElement(key, value));

	}
		
	void Delete(const Key& key) {
		
		const Hash hash = GetHash(key);
		List* const list_ptr = table_[hash];

		if (list_ptr->empty()) throw MapException(LIST_IS_EMPTY);

		size_t list_size = list_ptr->size();

		bool element_found = false;

		for (uint index = 0; index < list_size; index++)
		{

			ListElement& list_element = (*list_ptr)[index];
			element_found = (list_element.key == key);

			if (element_found) {

				list_ptr->erase(index);
				break;

			}

		}

		if (!element_found) throw MapException(TERMIN_NOT_FOUND);

	}

};
}
#endif