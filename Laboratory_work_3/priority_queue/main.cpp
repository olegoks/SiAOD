#include"forward_list.h"
#include"priority_queue.h"
#include<iostream>
static class Task final {

public:

	size_t input_takts_;
	size_t useful_takts_;

};

using Thread = lst::forward_list<Task>;
using ThreadsQueue = tl::priority_queue<Thread>;

static class Threads final {



private:
	
	ThreadsQueue threads_;

protected:


public:

	inline size_t size()const noexcept { return threads_.size(); }

	inline Thread& operator[](const size_t index)noexcept { return threads_[index].data_; }
	
	void insert(const Thread& thread, const tl::Priority priority)noexcept {

		threads_.insert(thread, priority);

	}

	inline Thread get(const tl::Priority search_priority) { return threads_.get(search_priority).data_; }
	inline Thread get() { return threads_.get().data_; }
	inline bool empty()const noexcept { return size() == 0; }
};

static class Cpu final {
private:

	const size_t interval_time_;
	size_t number_of_intervals_;
	size_t number_of_missed_takts_;
	bool cpu_is_counting_;

	void ProcessThread(Thread& thread)noexcept {

		Task task = thread.pop_front();

		if (cpu_is_counting_) {

			if (task.input_takts_ > 0) {

				if (task.input_takts_ < interval_time_)
					task.input_takts_ = 0;
				else
					task.input_takts_ -= interval_time_;

			}

			thread.push_front(task);

		}
		else {

			if (task.useful_takts_ > 0) {

				cpu_is_counting_ = true;

				if (task.useful_takts_ < interval_time_) {

					/*const size_t resudual_takts = interval_time_ - task.input_takts_;

					if (task.input_takts_ < resudual_takts)task.input_takts_ = 0;
					else
						task.input_takts_ -= resudual_takts;

					number_of_missed_takts_ += resudual_takts;*/

				}
				else
					task.input_takts_ -= interval_time_;


			}

		}
		
	}


public:

	inline size_t GetCommonNumberOfTakts()const noexcept { return interval_time_ * number_of_intervals_; }
	inline size_t GetMessedTakts()const noexcept { return number_of_missed_takts_; };

	explicit Cpu(const size_t interval_time)noexcept:
		interval_time_(interval_time), 
		number_of_intervals_(0),
		number_of_missed_takts_(0),
		cpu_is_counting_(false){}

	void operator << (Threads& threads) {

		const size_t number_of_threads = threads.size();

		for (size_t index = 0; index < number_of_threads; index++){

			Thread& current_thread = threads[index];
			ProcessThread(current_thread);

		}

		cpu_is_counting_ = false;
		number_of_intervals_++;

	}

};

int main() {

	Threads threads;
	Cpu CPU(3);
	threads.insert({ {0, 4},{3, 2},{3, 3} }, 1);
	threads.insert({ {0, 3},{3, 4},{3, 2} }, 2);
	threads.insert({ {0, 3},{3, 2},{3, 3} }, 2);

	for (size_t index = 0; index < threads.size(); index++){
		
		Thread& current_thread = threads[index];

		for (size_t i = 0; i < current_thread.size(); i++){

			Task current_task = current_thread[i];
			std::cout << current_task.input_takts_ << " " << current_task.useful_takts_ << " ";

		}
		
		std::cout << std::endl;
	}

	std::cout << std::endl;

	while (!threads.empty()) {

		 CPU << threads;

	}

	std::cout << "Common number of takts: " << CPU.GetCommonNumberOfTakts() << std::endl;
	std::cout << "Number of missed takts: " << CPU.GetMessedTakts() << std::endl;
	/*lst::forward_list<size_t> list{ 1, 2 ,3 ,4, 5 };
	lst::forward_list<size_t> list_2{ 5, 4 ,3 , 2, 1 };

	list_2 = list;*/
	system("pause");
	return 0;
}