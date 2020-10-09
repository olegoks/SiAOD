#pragma once
#ifndef _MULTIMAP_H_
#define _MULTIMAP_H_
#include <vector>

namespace mltmp {


	#include "forward_list.h"

		template<class key_type, class value_type>
		class multimap {

			struct list_element {
				key_type key;
				value_type value;
			};

			using list_type = lst::forward_list<list_element>;
			using table_type = std::vector<list_type*>;
			using key_value_type = int;
			using hash_type = unsigned int;
			using uint = unsigned int;

		private:

			table_type table_;

			hash_type HashFunction(key_value_type key) {

				return key % table_.size();

			}

			uint GetHash(const key_type& key) {

				key_value_type key_value = (key_value_type)key;
				uint hash = HashFunction(key_value);

				return hash;

			}

		public:

			explicit multimap(const uint size)noexcept {

				table_.clear();

				for (uint i = 0; i < size; i++)
				{

					table_.push_back((list_type*) new list_type);

				}
				

			}

			value_type& operator[](key_type key) {

				key_value_type key_value = key.operator=(key);
				hash_type hash = HashFunction(key_value);

				list_type* list_ptr = table_[hash];

				if (!list_ptr->empty()) {

					uint list_size = list_ptr->size();

					for (uint i = 0; i < list_size; i++)
					{

						if ((*list_ptr)[i].key == key){
							return (*list_ptr)[i].value;
						}

					}

				}

			}

			void Add(key_type key, value_type value) {

				key_value_type key_value = key.operator=(key);
				hash_type hash = HashFunction(key_value);

				list_type* list_ptr = table_[hash];

				list_ptr->push_back(list_element{key, value});

			}
			
		};
}
#endif