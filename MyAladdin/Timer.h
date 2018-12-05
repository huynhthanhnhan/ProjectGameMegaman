#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__
#include<Windows.h>
class Timer
{
public:
	Timer();
	~Timer();
	static Timer*		Instance();
	void				Start();
	float				Count();
private:
	LARGE_INTEGER timeStart, timeEnd, timeDelta, timeClockRate;
	static Timer* instance;
};

#endif __TIMER_H__