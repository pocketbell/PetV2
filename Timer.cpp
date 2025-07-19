#include "Timer.h"
#include <chrono>
#include <iostream>


std::chrono::steady_clock::time_point Timer::GetStartTime()
{
	return m_start;
}
void Timer::ResetStartTime()
{
	m_start = std::chrono::high_resolution_clock::now();
}
std::chrono::steady_clock::time_point Timer::GetEndTime()
{
	return m_end;
}
void Timer::ResetEndTime()
{
	m_end = std::chrono::high_resolution_clock::now();
}
std::chrono::duration<double> Timer::GetDurationTime()
{
	return m_duration;
}
void Timer::SetDurationTime()
{
	m_duration = std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start);
}
void Timer::CalculateDuration()
{
	ResetEndTime();
	SetDurationTime();
}
void Timer::SetDurationToSeconds()
{
	m_durationToSeconds = m_duration.count();
}
double Timer::GetDurationToSeconds()
{
	return m_durationToSeconds;
}
bool Timer::OneSecondPassed()
{
	CalculateDuration();
	SetDurationToSeconds();
	if (GetDurationToSeconds() > 1)
	{
		ResetStartTime();
		return true;
	}
	return false;
}