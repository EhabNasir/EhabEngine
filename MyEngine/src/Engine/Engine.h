#pragma once
#define FPS60 1.0f / 60.0f

#include "Core/Timer.h"

class Engine
{
public:
	void Run();

private:
	void Init();
	void Update(float _deltaTime);
	void FixedUpdate(float _fixedTime);
	void ShutDown();

	Timer m_timer;
	float accumulator = 0.0f;
	float maxAccumulator = 0.25f;

	bool m_isRunning = false;
};