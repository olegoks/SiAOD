#pragma once
#ifndef _BASE_LIST_H_
#define _BASE_LIST_H_

namespace nmspc {

	const int MAX = 100;

	class base_list {

	protected:

		unsigned int number_of_elements;

		inline bool indexIsCorrect(const unsigned int index) const noexcept {
			return (index >= 0) && (index < number_of_elements) && ((index + 1) <= MAX);
		}

	private:


	public:

		//constructor
		explicit base_list()noexcept : number_of_elements(0){};

		//methods realization
		inline unsigned int size() const noexcept { return number_of_elements; };
		inline char empty()const noexcept { return ( number_of_elements == 0 ); };
		inline int max_size()const noexcept { return MAX; }

		class ListException {
		private:

			const char* method_name_;

		public:

			inline const char* GetError()const noexcept { return method_name_; };

			explicit ListException(const char* method_name)noexcept :method_name_(method_name) {}

		};

	};

}

#endif