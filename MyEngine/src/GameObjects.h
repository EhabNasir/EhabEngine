#pragma once

struct Transform
{
	float x;
	float y;
};

struct RigidBody
{
	float xVelocity = 0;
	float yVelocity = 0;

	float mass = 1.0f;
};

class GameObjects
{
public:
	GameObjects();
	~GameObjects();

	Transform& GetTransform() { return m_Transform; }
	void SetTransform(float _x, float _y);

	RigidBody& GetRigidBody() { return m_RigidBody; }
	void SetRigidBody(float _xVelocity, float _yVelocity, float _mass);

private:
	Transform m_Transform;
	RigidBody m_RigidBody;
};