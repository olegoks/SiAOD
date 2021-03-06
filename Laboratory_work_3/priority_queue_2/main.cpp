#include "QueueList.h"
#include "priority_queue.h"
#include "Thread.h"
#include "Cpu.h"
#include <iomanip>
#include "output_constants.h"

void OutptTableHeader() {

	std::cout << "     |";
	for (size_t i = 1; i <= 10; i++){

		std::cout << std::setw(6) << i << "|";

	}

	std::cout << "  INPUT TICKS";

	std::cout << std::endl;
	std::cout << kSeparatorLine << std::endl;
}

struct MissedCommon {

	size_t misssed;
	size_t common;

};
//
MissedCommon info[10][10];
//
double StartSimulation(const size_t interval_ticks, const size_t input_ticks) {

	priority_queue<Thread> queue;

	const size_t input = input_ticks;
	//My
	/*queue.push({ { {3},{2},{1},{6},{3},{2},{5},{4} }, input, 1 }, 1);
	queue.push({ { {2},{1},{2},{3},{3},{1},{2},{6},{4} }, input, 1 }, 1);
	queue.push({ { {4},{1},{6},{8},{5},{4},{2},{3},{1},{2} }, input, 1 }, 1);
	queue.push({ { {2},{4},{8},{9},{3},{2},{1},{6},{5},{9} }, input, 2 }, 2);
	queue.push({ { {9},{6},{7},{2},{3},{1},{4},{5},{1},{3},{2} }, input, 2 }, 2);
	queue.push({ { {2},{3},{2},{1},{6},{3},{4},{1},{2},{3},{1} }, input, 3 }, 3);
	queue.push({ { {3},{2},{3},{1},{3},{4},{1},{2},{1},{6},{1},{2} }, input, 3 }, 3);
	queue.push({ { {2},{3},{3},{3},{1},{6},{3},{8},{4},{2},{2},{2} }, input,3 }, 3);*/

	//valya
	queue.push({ { {2},{4},{3},{1},{5},{2},{4},{3},{1},{2},{3} }, input, 1 }, 1);
	queue.push({ { {1},{3},{2},{1},{5},{4},{3},{1},{2},{3},{4} }, input, 2 }, 2);
	queue.push({ { {4},{2},{1},{3},{4},{5},{2},{1},{4},{5},{1} }, input, 2 }, 2);
	queue.push({ { {2},{4},{3},{2},{4},{3},{1},{4},{5},{3} }, input, 3 }, 3);
	queue.push({ { {4},{3},{2},{1},{3},{2},{1},{5},{4},{2} }, input, 3 }, 3);
	queue.push({ { {4},{1},{2},{3},{4},{1},{3},{8},{7},{5} }, input, 3 }, 3);

	//Marian
	/*queue.push({ { {2},{2},{3},{4},{2},{1},{1},{3},{3},{1} }, input, 1 }, 1);
	queue.push({ { {4},{1},{1},{1},{1},{2},{2},{3},{1},{3},{3},{2} }, input, 1 }, 1);
	queue.push({ { {2},{1},{3},{2},{4},{5},{4},{2},{2},{2} }, input, 1 }, 1);
	queue.push({ { {4},{5},{4},{2},{3},{3},{3},{4},{3},{5},{3} }, input, 1 }, 1);
	queue.push({ { {1},{4},{3},{5},{4},{2},{3},{2},{3} }, input, 2 }, 2);*/

	//Desk test
	/*queue.push({ { {4},{2},{3} }, input, 1 }, 1);
	queue.push({ { {3},{4},{2} }, input, 2 }, 2);
	queue.push({ { {3},{2},{3} }, input, 2 }, 2);*/


	Cpu CPU(interval_ticks);

	if (interval_ticks == 4 && input_ticks == 4)
		size_t a = 10;
	
	while (!queue.empty()) 
		CPU << queue;

	const double kCommonTicks = static_cast<double>(CPU.get_common_ticks());
	const double kMissedTicks = static_cast<double>(CPU.get_missed_ticks());
	const double kUsefullTicks = kCommonTicks - kMissedTicks;
	//
	info[interval_ticks - 1][input_ticks - 1].misssed = kMissedTicks;
	info[interval_ticks - 1][input_ticks - 1].common = kCommonTicks;
	//
	return kUsefullTicks / kCommonTicks;
}

int main() {

	std::cout.precision(kKpdPrecision);

	OutptTableHeader();

	for (size_t interval_ticks = 1; interval_ticks <= 10; interval_ticks++){
		
		std::cout.width(kCellWidth);
		std::cout << interval_ticks << kVerticalSeparator;

		for (size_t input_ticks = 1; input_ticks <= 10; input_ticks++){

			const double kpd =  StartSimulation(interval_ticks, input_ticks);
			std::cout.width(kCellWidth);
			std::cout << kpd << kSpace<< kVerticalSeparator;

		}

		std::cout << std::endl;
		std::cout << kSeparatorLine;
		std::cout << std::endl;

	}

	std::cout << "C\nP\nU\n \nT\nI\nC\nK\nS\n";
	//

	for (size_t interval_ticks = 1; interval_ticks <= 10; interval_ticks++) {

		std::cout.width(7);
		std::cout << interval_ticks << kVerticalSeparator;

		for (size_t input_ticks = 1; input_ticks <= 10; input_ticks++) {

			std::cout.width(7);
			std::cout << info[interval_ticks - 1][input_ticks -1 ].misssed << kSpace << info[interval_ticks -1 ][input_ticks - 1].common << kSpace << kVerticalSeparator;

		}

		std::cout << std::endl;
		std::cout << kSeparatorLine << kSeparatorLine;
		std::cout << std::endl;

	}

	//
	system("pause");

	return EXIT_SUCCESS;
}




/*queue.push(Thread{ {{0, 4}, {3, 2}, {3, 3}}, 1 }, 1);
queue.push(Thread{ {{0, 3}, {3, 4}, {3, 2}}, 2 }, 2);
queue.push(Thread{ {{0, 3}, {3, 2}, {3, 3}}, 2 }, 2);*/

//priority_queue<Thread> queue;

/*queue.push(Thread{ {{0, 4}, {3, 2}, {3, 3}}, 1 }, 1);
queue.push(Thread{ {{0, 3}, {3, 4}, {3, 2}}, 2 }, 2);
queue.push(Thread{ {{0, 3}, {3, 2}, {3, 3}}, 2 }, 2);*/
/*const size_t input = 3;
queue.push(Thread{ { {3},{2},{1},{6},{3},{2},{5},{4} }, input, 1 }, 1);
queue.push(Thread{ { {2},{1},{2},{3},{3},{1},{2},{6},{4} }, input, 1 }, 1);
queue.push(Thread{ { {4},{1},{6},{8},{5},{4},{2},{3},{1},{2} }, input, 1 }, 1);
queue.push(Thread{ { {2},{4},{8},{9},{3},{2},{1},{6},{5},{9} }, input, 2 }, 2);
queue.push(Thread{ { {9},{6},{7},{2},{3},{1},{4},{5},{1},{3},{2} }, input, 2 }, 2);
queue.push(Thread{ { {2},{3},{2},{1},{6},{3},{4},{1},{2},{3},{1} }, input, 3 }, 3);
queue.push(Thread{ { {3},{2},{3},{1},{3},{4},{1},{2},{1},{6},{1},{2} }, input, 3 }, 3);
queue.push(Thread{ { {2},{3},{3},{3},{1},{6},{3},{8},{4},{2},{2},{2} }, input,3 }, 3);
Cpu CPU(2);

while (!queue.empty()) {

	CPU << queue;*/

	//const size_t priorities_number = queue.low_priority();

	//for (size_t priority = 1; priority <= priorities_number; priority++){

	//	const size_t number_of_threads = queue.elements_number(priority);

	//	for (size_t thread_index = 0; thread_index < number_of_threads; thread_index++){

	//		Thread& thread = queue(priority, thread_index);
	//		std::cout << "Thread identifier: " << thread.identifier_ << std::endl;
	//		const size_t thread_size = thread.size();

	//		for (size_t i = 0; i < thread_size; i++){

	//			Task& task = thread[i];
	//			std::cout << thread.priority_ << "  " << task.input_ticks << " " << task.cpu_ticks << std::endl;

	//		}

	//	}

	//}

	//std::cout << "Missed ticks: " << CPU.get_missed_ticks() << std::endl;
	//std::cout << "Common ticks: " << CPU.get_common_ticks() << std::endl;

	//system("pause");
	//system("cls");

/*}

std::cout << "Simulation ended successfull." << std::endl;
std::cout << "Missed ticks: " << CPU.get_missed_ticks() << std::endl;
std::cout << "Common ticks: " << CPU.get_common_ticks() << std::endl;*/

//system("pause");


