#include "Cpu.h"

using uint = unsigned int;


void Cpu::ProcessThreadInput(Thread& thread)const noexcept {

	Task task = thread.pop_front();
	
	if (task.input_takts_ <= interval_time_) 
		task.input_takts_ = 0;
	else 
		task.input_takts_ -= interval_time_;

	thread.push_front(task);

}
void Cpu::ProcessThread(Thread& thread)noexcept {
	//If processor processing some task
	
	
	if (cpu_is_counting_) ProcessThreadInput(thread);

	//Processor is free
	else {

		uint work_takts = interval_time_;

		////Process task
		//if (!input_required) {

		//	if (task.useful_takts_ <= work_takts) {

		//		work_takts -= task.useful_takts_;
		//		task.useful_takts_ = 0;
		//	}
		//	else {

		//		task.useful_takts_ -= work_takts;
		//		work_takts = 0;

		//	}
		//	cpu_is_counting_ = true;
		//}

		//if (input_required && work_takts) {

		//	//Process Input
		//	if (task.input_takts_ <= work_takts) {

		//		work_takts -= task.input_takts_;
		//		task.input_takts_ = 0;
		//		input_required = false;

		//	}
		//	else {

		//		task.input_takts_ -= work_takts;
		//		work_takts = 0;
		//	}
		//}

		/*bool task_not_completed = task.useful_takts_;
		if (task_not_completed)thread.push_front(task);*/

	}

}

void Cpu::operator << (ThreadsQueue& threads) {

	const uint number_of_threads = threads.size();

	static size_t last_process_thread_id = 0;

	for (uint index = 0; index < number_of_threads; index++) {
		
		Thread& current_thread = threads[index].data_;
		tl::Priority thread_priority = threads[index].priority_;
		size_t thread_id = current_thread.GetId();
		
		ProcessThread(current_thread);
			
	}

	cpu_is_counting_ = false;
	number_of_intervals_++;

}

Cpu::Cpu(const uint interval_time)noexcept:
	interval_time_(interval_time),
	number_of_intervals_(0),
	number_of_missed_takts_(0),
	cpu_is_counting_(false) {}