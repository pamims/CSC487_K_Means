#ifndef ALEX_MIMS_BENCHMARK_TIMER_H
#define ALEX_MIMS_BENCHMARK_TIMER_H

#include <chrono>

namespace test {
	class Timer {
	private:
		std::chrono::steady_clock::time_point mark;
	public:
		Timer() noexcept;
		void   Set()  noexcept;
		double Mark() noexcept;
		double Peek() const noexcept;
	};
}

#endif

