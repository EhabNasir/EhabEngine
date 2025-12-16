#pragma once

class ISystem
{
public:
	virtual ~ISystem() = default;

	virtual void Update(float _deltaTime);
	virtual void FixedUpdate(float _fixedDelta);

};