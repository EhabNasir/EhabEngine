#pragma once
#define FPS60 1.0f / 60.0f

#include "Core/Timer.h"
#include "Interfaces/ISystems.h"

#include <vector>
#include <memory>

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

	std::vector<std::unique_ptr<ISystem>> m_systems;

	bool m_isRunning = false;
};