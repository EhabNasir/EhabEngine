#pragma once
#include "Interfaces/ISystems.h"

class System_Physics : public ISystem
{
public:
	void FixedUpdate(float _fixedDelta) override;

private:
};