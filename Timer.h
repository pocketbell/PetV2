#pragma once
#include <chrono>


class Timer
{
	std::chrono::steady_clock::time_point m_start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point m_end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> m_duration{ 0 };
	double m_durationToSeconds{ 0 };
public:
	std::chrono::steady_clock::time_point GetStartTime();
	void ResetStartTime();
	std::chrono::steady_clock::time_point GetEndTime();
	void ResetEndTime();
	std::chrono::duration<double> GetDurationTime();
	void SetDurationTime();
	void CalculateDuration();
	void SetDurationToSeconds();
	double GetDurationToSeconds();
	bool OneSecondPassed();
};