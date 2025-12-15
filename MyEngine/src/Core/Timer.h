#pragma once
#include <chrono>

class Timer
{
public: 
	Timer();
	void Reset();
	float GetDeltaTime();

private:
	using clock = std::chrono::steady_clock;
	std::chrono::steady_clock::time_point m_lastFrame;
};