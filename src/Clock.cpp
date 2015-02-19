#include <Clock.hpp>

#include <ctime>

namespace zeno {

Clock::Clock(void) :
m_StartTime(getCurrentTime())
{
}
Clock::~Clock(void)
{
}

Time Clock::getElapsedTime(void)
{
	return getCurrentTime() - m_StartTime;
}
Time Clock::restart(void)
{
	Time now = getCurrentTime();
	Time elapsed = now - m_StartTime;
	m_StartTime = now;
	
	return elapsed;
}

Time Clock::getCurrentTime(void)
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	
	return Time::microseconds(static_cast<long long>(time.tv_sec) * 1000000 + time.tv_nsec / 1000);
}

} //~ namespace zeno
