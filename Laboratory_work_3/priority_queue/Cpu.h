#pragma once

#ifndef _CPU_H_
#define _CPU_H_

#include "ThreadsQueue.h"

using uint = unsigned int;

class Cpu final {

private:

	const uint interval_time_;
	uint number_of_intervals_;
	uint number_of_missed_takts_;
	bool cpu_is_counting_;

	void ProcessThread(Thread& thread)noexcept;

public:

	inline uint GetCommonNumberOfTakts()const noexcept { return interval_time_ * number_of_intervals_; }
	inline uint GetMessedTakts()const noexcept { return number_of_missed_takts_; };
	explicit Cpu(const uint interval_time)noexcept;
	void operator << (ThreadsQueue& threads);

};

#endif

