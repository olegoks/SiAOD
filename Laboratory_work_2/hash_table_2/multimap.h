#pragma once
#ifndef _MULTIMAP_H_
#define _MULTIMAP_H_
#include <vector>

namespace mp {

#include "forward_list.h"

template<class Key, class Value>
class map {

	struct ListElement {
		Key key;
		Value value;

		explicit ListElement()noexcept: key(), value() {

		}
	};

	using List = lst::forward_list<ListElement>;
	using HashTable = std::vector<List*>;
	using KeyValue = int;
	using Hash = unsigned int;
	using uint = unsigned int;

	private:

	HashTable table_;

	inline Hash ReturnHash(KeyValue key) const{

		return key % table_.size();

	}

	uint GetHash(const Key& key)const {

		const KeyValue key_value = (KeyValue)key;
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

		if (!list_ptr->empty()) {

			uint list_size = list_ptr->size();

			for (uint i = 0; i < list_size; i++)
			{

				const ListElement list_element = (*list_ptr)[i];
				const bool element_found = list_element.key == key;

				if (element_found) return list_element.value;

			}

			///Throw except.

		}

	}

	void Add(const Key& key,const Value& value) {

		const Hash hash = GetHash(key);
		List* const list_ptr = table_[hash];

		list_ptr->push_back(List{key, value});

	}
		
	void Delete(const Key& key) {



	}

};
}
#endif