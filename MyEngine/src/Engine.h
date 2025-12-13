#pragma once
#include <chrono>

class Engine
{
public:
	void Run();

private:
	void Init();
	void Tick(float _deltaTime);
	void ShutDown();

	using clock = std::chrono::steady_clock;
	clock::time_point m_lastTime;

	bool m_isRunning;
};