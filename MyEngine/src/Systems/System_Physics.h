#pragma once
#include "Interfaces/ISystems.h"
#include "GameObjects.h"

#include<vector>
#include<memory>

class System_Physics : public ISystem
{
public:
	~System_Physics();

	void Update(float _deltaTime) override;
	void FixedUpdate(float _fixedDelta) override;

	void InstantiateGameObject();

private:
	std::vector<GameObjects*> m_GameObjects;
};