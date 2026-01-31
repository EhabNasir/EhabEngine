#pragma once
#include "Core/Vector3.h";

class Transform
{
public:
	Transform();
	~Transform();

	Vector3 GetTransform() { return m_Position; }

	void SetPosition(float _x, float _y) { m_Position.x = _x; m_Position.y = _y; }
	void SetPosition(Vector3 _position) { m_Position = _position; }

private:
	Vector3 m_Position;
};