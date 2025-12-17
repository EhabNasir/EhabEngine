#pragma once
#include <vector>

#include "Interfaces/ISystems.h"
#include "Interfaces/IRenderer.h"
#include "GameObjects.h"

class System_Renderer : public ISystem
{
public:
	System_Renderer(IRenderer& _render);

	void Update(float deltaTime) override;
	void FixedUpdate(float) override {}

	void Register(GameObjects* _gameObjects);

private:
	IRenderer& m_renderer;
	std::vector<GameObjects*> m_objects;
};