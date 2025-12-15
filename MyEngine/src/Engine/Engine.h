#pragma once
#include <chrono>
#include "Core/Timer.h"

class Engine
{
public:
	void Run();

private:
	void Init();
	void Tick(float _deltaTime);
	void ShutDown();

	Timer m_timer;

	bool m_isRunning;
};