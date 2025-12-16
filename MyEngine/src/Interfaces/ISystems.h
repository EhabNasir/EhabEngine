#pragma once

class ISystem
{
public:
	virtual ~ISystem() = default;

	virtual void Update(float _deltaTime) = 0;
	virtual void FixedUpdate(float _fixedDelta) = 0;
};