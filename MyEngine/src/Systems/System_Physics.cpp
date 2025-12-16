#include "System_Physics.h"
#include "Core/Debug.h"

void System_Physics::Update(float _deltaTime)
{

}

void System_Physics::FixedUpdate(float _fixedDelta)
{
	float gravity = -9.8f;

	for (auto& gameObject : m_GameObjects)
	{
		auto& transform = gameObject->GetTransform();
		auto& body = gameObject->GetRigidBody();

		body.yVelocity += (gravity/body.mass) * _fixedDelta;
		transform.y += body.yVelocity * _fixedDelta;

		Debug::PrintNumber(transform.y);
	}
}

void System_Physics::InstantiateGameObject()
{
	GameObjects* obj = new GameObjects();
	m_GameObjects.push_back(obj);
}

System_Physics::~System_Physics()
{
	for (auto& gameObject : m_GameObjects)
	{
		delete gameObject;
	}
}