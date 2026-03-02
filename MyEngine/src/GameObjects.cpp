#include "GameObjects.h"
#include "Core/Debug.h"
#include <string>
#include <iostream>

GameObjects::GameObjects()
{
	m_Transform = new Transform();
	m_Transform->SetPosition(0, 100);

	m_RigidBody.mass = 0.5f;
}

void GameObjects::SetRigidBody(float _xVelocity, float _yVelocity, float _mass)
{
	m_RigidBody.xVelocity = _xVelocity;
	m_RigidBody.yVelocity = _yVelocity;

	m_RigidBody.mass = _mass;
}

GameObjects::~GameObjects()
{

}