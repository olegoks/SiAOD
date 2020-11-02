
#include<iostream>
#include"ThreadsQueue.h"
#include"Cpu.h"


int main() {

	ThreadsQueue threads;
	Cpu CPU(2);

	threads.insert({ {0, 4},{3, 2},{3, 3} }, 1);
	threads.insert({ {0, 3},{3, 4},{3, 2} }, 2);
	threads.insert({ {0, 3},{3, 2},{3, 3} }, 2);

	for (size_t index = 0; index < threads.size(); index++){
		
		Thread& current_thread = threads[index].data_;

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