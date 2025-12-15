#include "Timer.h"

Timer::Timer()
{
	m_lastFrame = clock::now();
}

void Timer::Reset()
{
	m_lastFrame = clock::now();
}

float Timer::GetDeltaTime()
{
	auto now = clock::now();

	std::chrono::duration<float> delta = now - m_lastFrame;

	float deltaTime = delta.count();

	m_lastFrame = now;

	return deltaTime;
}

