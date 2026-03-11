#include "System_Physics.h"
#include "Core/Debug.h"

void System_Physics::Update(float _deltaTime)
{

}

void System_Physics::FixedUpdate(float _fixedDelta)
{
	gravity += _fixedDelta;

	for (auto& gameObject : m_GameObjects)
	{
		auto* transform = gameObject->GetTransform();
		auto& body = gameObject->GetRigidBody();

		//body.yVelocity += (gravity/body.mass) * _fixedDelta;

		transform->SetPosition(0.0f, gravity);
		//transform->SetPosition.y += body.yVelocity * _fixedDelta;
	}
}

void System_Physics::InstantiateGameObject()
{
	GameObjects* obj = new GameObjects();
	obj->GetTransform()->SetPosition(0.0f, 0.0f);
	m_GameObjects.push_back(obj);
}

System_Physics::~System_Physics()
{
	for (auto& gameObject : m_GameObjects)
	{
		delete gameObject;
	}
}