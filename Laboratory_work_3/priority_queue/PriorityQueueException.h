#pragma once
#ifndef _PRIORITYQUEUEEXCEPTION_H_
#define  _PRIORITYQUEUEEXCEPTION_H_

#include<string>
namespace tl {
	class PriorityQueueException
	{
	private:
		std::string error_name_;
	protected:
	public:
		explicit PriorityQueueException()noexcept :error_name_("Priority queue exception.") {}
		explicit PriorityQueueException(const std::string& error_name)noexcept :error_name_(error_name) {}
	};
}
#endif

