#include <chrono>

#include "Timer.h"

Timer::Timer()
{
	m_lastFrame = clock::now();
}

float Timer::GetDeltaTime()
{
	auto now = clock::now();

	std::chrono::duration<float> delta = now - m_lastFrame;

	float deltaTime = delta.count();

	return deltaTime;
}