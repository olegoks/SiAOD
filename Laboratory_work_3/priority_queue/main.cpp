#include"forward_list.h"
#include"priority_queue.h"

class Task final {

public:

	size_t input_takts_;
	size_t useful_takts_;

};

	

class Tasks final {
private:

	tl::priority_queue<lst::forward_list<Task>> tasks_;

protected:


public:

	inline const lst::forward_list<Task>& operator[](const size_t index)const noexcept {return tasks_[index];}

};

int main() {



	

	return 0;
}