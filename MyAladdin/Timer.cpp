#include "Timer.h"

Timer*			Timer::instance = new Timer();

Timer::Timer()
{
}


Timer::~Timer()
{
}

Timer* Timer::Instance()
{
	if (!instance)
		instance = new Timer();
	return instance;
}

void Timer::Start()
{
	if (!QueryPerformanceFrequency(&timeClockRate))
		return;
	QueryPerformanceCounter(&timeStart);
}

float Timer::Count()
{
	QueryPerformanceCounter(&timeEnd);
	timeDelta.QuadPart = timeEnd.QuadPart - timeStart.QuadPart;
	return (float)(timeDelta.QuadPart / timeClockRate.QuadPart);
}
