#pragma once
#ifndef _RING_LIST_H_
#define _RING_LIST_H_

namespace rng {

	typedef unsigned int uint;


	struct Element {

		uint index;
		Element* next;
		Element(uint index_, Element* next_) :index(index_), next(next_) {

		}
	};


	class iterator {
	private:

		Element* pointer_;

	public:

		explicit iterator(Element* pointer) noexcept :pointer_(pointer) {

		}
		void operator++() {

			pointer_ = pointer_->next;

		}

		uint operator* () {

			return (pointer_->next)->index;

		}
		inline Element* GetAdress()const noexcept{
			return pointer_;
		}

	};

	class ring_list {

	private:

		uint number_of_elements_;
		Element* head_;
		Element* ass_;

	public:

		explicit ring_list()noexcept : head_(new Element(0, nullptr)), number_of_elements_(0) {

		}

		inline uint size()const noexcept {

			return number_of_elements_;

		}

		void create(const uint number_of_elements) {

			Element* ptr = head_;

			for (uint i = 0; i < number_of_elements; i++) {

				ptr->next = new Element(i + 1, nullptr);
				ptr = ptr->next;

			}

			ptr->next = head_->next;
			ass_ = ptr;
			number_of_elements_ = number_of_elements;

		}

		void clear() {

			if (number_of_elements_ > 0) {

				Element* ptr_delete = head_->next, * ptr_next;
				head_->next = nullptr;

				for (uint i = 0; i < number_of_elements_; i++)
				{
					ptr_next = ptr_delete->next;
					if (ptr_delete != nullptr)delete ptr_delete;
					ptr_delete = ptr_next;
				}

			}

			this->number_of_elements_ = 0;
		}

		void erase(iterator it) {

			Element* ptr_previous = it.GetAdress();
			Element* ptr_current = ptr_previous->next;
			ptr_previous->next = ptr_current->next;
			if (ptr_current == head_->next)head_->next = ptr_previous->next;
			if (ptr_current == ass_)ass_ = ptr_previous;
			delete ptr_current;
			number_of_elements_--;

		}

		inline iterator begin()const noexcept {

			return iterator(ass_);

		}

	};

}
#endif