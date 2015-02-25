#include <Clock.hpp>

#ifdef _WIN32
#include <Windows.h>
#else
#include <ctime>
#endif //~ _WIN32

#ifdef _WIN32
namespace
{
	LARGE_INTEGER getFrequency()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency;
	}
}
#endif //~ _WIN32

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
#ifdef _WIN32
Time Clock::getCurrentTime()
{
	// Force the following code to run on first core
	// (see http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx)
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

	// Get the frequency of the performance counter
	// (it is constant across the program lifetime)
	static LARGE_INTEGER frequency = getFrequency();

	// Get the current time
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	// Restore the thread affinity
	SetThreadAffinityMask(currentThread, previousMask);

	// Return the current time as microseconds
	return Time::microseconds(1000000 * time.QuadPart / frequency.QuadPart);
}
#else
Time Clock::getCurrentTime(void)
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	
	return Time::microseconds(static_cast<long long>(time.tv_sec) * 1000000 + time.tv_nsec / 1000);
}
#endif //~ _WIN32

} //~ namespace zeno
