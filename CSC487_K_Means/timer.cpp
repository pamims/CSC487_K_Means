#include "timer.h"

using namespace std::chrono;

namespace test {

	Timer::Timer() noexcept {
		mark = steady_clock::now();
	}

	void Timer::Set() noexcept {
		mark = steady_clock::now();
	}

	double Timer::Mark() noexcept {
		const auto temp = steady_clock::now();
		const duration<double> delta_time = temp - mark;
		mark = temp;
		return delta_time.count();
	}

	double Timer::Peek() const noexcept {
		return duration<double>(steady_clock::now() - mark).count();
	}
}