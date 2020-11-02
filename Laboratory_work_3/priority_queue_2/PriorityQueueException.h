#pragma once
#ifndef _PRIORITYQUEUEEXCEPTION_H_
#define _PRIORITYQUEUEEXCEPTION_H_

#include <string>

class PriorityQueueException
{
private:

	std::string error_;

protected:
public:

	explicit PriorityQueueException(const std::string& error)noexcept:
		error_(error){}

	const std::string& what()const noexcept { return error_; }

};

#endif

