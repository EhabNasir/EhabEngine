#pragma once
#define FPS60 1.0f / 60.0f

#include "Core/Timer.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "Interfaces/ISystems.h"
#include "Systems/System_Physics.h"
#include "Interfaces/IRenderer.h"

class Engine
{
public:
	void Run();

private:
	void Init();
	void Update(float _deltaTime);
	void FixedUpdate(float _fixedTime);
	void ShutDown();

	GLFWwindow* window = nullptr;

	Timer m_timer;
	float accumulator = 0.0f;
	float maxAccumulator = 0.25f;

	std::vector<std::unique_ptr<ISystem>> m_systems;
	std::unique_ptr<IRenderer> m_renderer;

	bool m_isRunning = false;
};