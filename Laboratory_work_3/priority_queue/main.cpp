#include"forward_list.h"
#include"priority_queue.h"

//static class Task final {
//
//public:
//
//	size_t input_takts_;
//	size_t useful_takts_;
//
//};
//
//	
//
//static class Tasks final {
//private:
//
//	tl::priority_queue<lst::forward_list<Task>> tasks_;
//
//protected:
//
//
//public:
//
//	inline lst::forward_list<Task>& operator[](const size_t index)const noexcept {return tasks_[index].data_;}
//
//};

int main() {

	tl::priority_queue<int> queue;

	queue.add(10, 1);
	queue.add(2, 2);
	queue.add(5,1);



	

	return 0;
}