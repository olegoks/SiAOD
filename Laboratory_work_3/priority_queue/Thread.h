#pragma once
#ifndef _THREAD_H_
#define _THREAD_H_

#include "forward_list.h"

using uint = unsigned int;

class Task final {

public:

	uint input_takts_;
	uint useful_takts_;

};

class Thread final : public lst::forward_list<Task> {

private:

	static uint last_identifier;
	const uint identifier_;

protected:
public:

	inline uint GetId()const noexcept { return identifier_; }

	explicit Thread()noexcept :
		lst::forward_list<Task>{},
		identifier_{ last_identifier } {

		last_identifier++;

	}

	Thread(const std::initializer_list<Task>& init_list)noexcept :
		lst::forward_list<Task>{ init_list },
		identifier_{ last_identifier }{

		last_identifier++;

	}

	Thread& operator=(const Thread& list)noexcept {

		lst::forward_list<Task>::operator=(list);
		return *this;
	}

	Thread& operator=(Thread&& list)noexcept {

		lst::forward_list<Task>::operator=(list);
		return *this;
	}

	Thread(const Thread& thread)noexcept:
		lst::forward_list<Task>(thread), 
		identifier_(last_identifier) {
		last_identifier++;
	}


};



#endif