#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_

#include "forward_list.h"

struct Task final {

	size_t input_ticks;
	size_t cpu_ticks;
	
	/*Task(const size_t input_ticks)noexcept :input_ticks{ input_ticks }, cpu_ticks{} {}
	Task(const size_t input_ticks, const size_t cpu_ticks)noexcept : input_ticks(input_ticks),
		cpu_ticks(cpu_ticks) {}*/
};

struct Thread final: public lst::forward_list<Task> {

	using List = lst::forward_list<Task>;

	static size_t identifier_;
	size_t id_;
	size_t priority_;

	explicit Thread()noexcept :
		id_{ identifier_ },
		priority_{ 0 },
		List{}{

		identifier_++;

	}
	
	explicit Thread(const std::initializer_list<Task>& initializer_list, const size_t priority)noexcept :
		List{ initializer_list },
		priority_{ priority },
		id_{ identifier_ }{ identifier_++; }

	explicit Thread(const std::initializer_list<size_t>& initializer_list, const size_t input_ticks, const size_t priority)noexcept :
		priority_{priority},
		id_{ identifier_ }{ 

		identifier_++; 

		for (const auto& list_obj : initializer_list)
			List::push_back(Task{input_ticks, list_obj});
		
	}
		
	

	void operator=(Thread&& thread)noexcept {

		List::operator=(std::move(thread));
		this->id_ = thread.id_;
		this->priority_ = thread.priority_;

	}

	const Thread& operator=(const Thread& thread)noexcept {

		List::operator=(thread);
		this->id_ = thread.id_;
		this->priority_ = thread.priority_;

		return *this;
	}

	Thread(Thread&& thread)noexcept :List{ std::move(thread) } {

		this->id_ = thread.id_;
		this->priority_ = thread.priority_;

		
	} 

	Thread(const Thread& thread)noexcept :List{ thread } {

		this->id_ = thread.id_;
		this->priority_ = thread.priority_;

	}
};


#endif
