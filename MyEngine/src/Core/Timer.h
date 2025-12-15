#pragma once

class Timer
{
public: 
	Timer();
	float GetDeltaTime();

private:
	using clock = std::chrono::steady_clock;
	std::chrono::steady_clock::time_point m_lastFrame;
};