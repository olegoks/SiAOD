#pragma once
#ifndef _THREADS_QUEUE_H_
#define _THREADS_QUEUE_H_

#include "priority_queue.h"
#include "Thread.h"

using uint = unsigned int;

class ThreadsQueue final:public tl::priority_queue<Thread> {

private:

protected:

public:

	//inline size_t size()const noexcept { return tl::priority_queue<Thread>::size(); }

	inline QueueElement& operator[](const uint index)noexcept { return tl::priority_queue<Thread>::operator[](index); }
	inline size_t priorityNumber(const tl::Priority priority)const noexcept { return tl::priority_queue<Thread>::priorityNumber(priority); }
	
	/*void insert(const Thread& thread, const tl::Priority priority)noexcept {

		tl::priority_queue<Thread>::insert(thread, priority);

	}*/

	//inline Thread get(const tl::Priority search_priority) { return tl::priority_queue<Thread>::get(search_priority).data_; }
	//inline Thread get() { return tl::priority_queue<Thread>::get().data_; }
	//inline bool empty()const noexcept { return size() == 0; }
};

#endif
