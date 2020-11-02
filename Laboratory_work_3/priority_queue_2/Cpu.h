#pragma once
#ifndef _CPU_H_
#define _CPU_H_

#include "Thread.h"
#include "priority_queue.h"

const size_t kFIRST = 0;

class Cpu final {
private:

	size_t interval_duration_;
	size_t missed_ticks_;
	size_t common_number_of_ticks_;
	bool cpu_is_free_;

	void ProcessTaskInput(Task& task, size_t& available_cpu_ticks)const noexcept {

		if (task.input_ticks > 0) {

			if (task.input_ticks >= available_cpu_ticks) {
				task.input_ticks -= available_cpu_ticks;
				available_cpu_ticks = 0;
			}
			else {

				available_cpu_ticks -= task.input_ticks;
				task.input_ticks = 0;

			}

		}

	}

	void ProcessTaskCpu(Task& task, size_t& available_cpu_ticks)noexcept {

		if (task.cpu_ticks > 0) {

			if (task.cpu_ticks >= available_cpu_ticks){

				task.cpu_ticks -= available_cpu_ticks;
				available_cpu_ticks = 0;

			}
			else {

				available_cpu_ticks -= task.cpu_ticks;
				task.cpu_ticks = 0;

			}

			this->missed_ticks_ += available_cpu_ticks;
			this->cpu_is_free_ = false;

		}

	}

	bool TaskIsDone(const Task& task)const noexcept {

		if (!task.cpu_ticks && !task.input_ticks)return true;

		return false;

	}
	inline bool TaskNeedInput(const Task& task)const noexcept { return task.input_ticks; }

	void ProcessThreadCpu(Thread& thread) {

		bool there_are_tasks = !thread.empty();

		if (there_are_tasks) {

			size_t available_cpu_ticks = this->interval_duration_;
			bool next_task = true;

			while (next_task) {

				Task task = thread.pop_front();
				bool input_required = (task.input_ticks > 0);

				if (!input_required) {

					if (this->cpu_is_free_)
						ProcessTaskCpu(task, available_cpu_ticks);

				}
				else
					ProcessTaskInput(task, available_cpu_ticks);

				if (!TaskIsDone(task)) {

					thread.push_front(task);
					next_task = false;

				}
				else {
					
					there_are_tasks = !thread.empty();
					if (!there_are_tasks || !available_cpu_ticks)
						next_task = false;

				}

			}

		}

	}

	void ProcessThreadInput(Thread& thread) {

		bool there_are_tasks = !thread.empty();

		if (there_are_tasks) {

			size_t available_cpu_ticks = this->interval_duration_;
			bool next_task = true;

			while (next_task) {

				Task task = thread.pop_front();
				bool input_required = (task.input_ticks > 0);

				if (input_required)
					ProcessTaskInput(task, available_cpu_ticks);
				
				if (!TaskIsDone(task)) {
					thread.push_front(task);
					next_task = false;
				}

			}

		}

	}

	bool ThreadIsEmpty(const Thread& thread)const noexcept {

		if (thread.empty()) return true;
		return false;

	}

	void ProcessThreadsInput(priority_queue<Thread>& threads, const size_t priority) {

		size_t el_num_this_priority = threads.elements_number(priority);

		for (size_t thread_index = 0; thread_index < el_num_this_priority; thread_index++){

			ProcessThreadInput(threads(priority, thread_index));

		}

	}

	bool ThreadNeedCpu(const Thread& thread)const noexcept {

		if (!thread.empty()) {

			const Task& first_task = thread[kFIRST];
			return !TaskNeedInput(first_task);

		}
		
		return false;

	}

protected:
public:

	void operator << (priority_queue<Thread>& threads) {

		const size_t number_of_priorities = threads.low_priority();
		this->cpu_is_free_ = true;
		this->common_number_of_ticks_ += this->interval_duration_;

		for (size_t thread_priority = 1; thread_priority <= number_of_priorities; thread_priority++){

			size_t el_num_this_priority = threads.elements_number(thread_priority);
			bool there_is_thread = el_num_this_priority;

			if (there_is_thread) {
				bool thread_need_cpu = ThreadNeedCpu(threads(thread_priority, kFIRST));
				if (this->cpu_is_free_ && thread_need_cpu) {

					Thread thread = threads.pop(thread_priority);
					ProcessThreadCpu(thread);
					ProcessThreadsInput(threads, thread_priority);
					if (!ThreadIsEmpty(thread))
						threads.push(thread, thread.priority_);

				}
				else
					ProcessThreadsInput(threads, thread_priority);

			}
	
		}
		
		if (this->cpu_is_free_) this->missed_ticks_ += this->interval_duration_;

		this->cpu_is_free_ = true;
	}

	inline size_t get_missed_ticks()const noexcept { return this->missed_ticks_; }
	inline size_t get_common_ticks()const noexcept { return this->common_number_of_ticks_; }
	explicit Cpu(const size_t interval_duration)noexcept:
		interval_duration_{ interval_duration },
		missed_ticks_{ 0 },
		common_number_of_ticks_(0),
		cpu_is_free_{ true }{}

};

#endif //_CPU_H_

