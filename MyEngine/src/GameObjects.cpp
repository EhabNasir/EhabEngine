#include "GameObjects.h"
#include "Core/Debug.h"
#include <string>
#include <iostream>

GameObjects::GameObjects()
{
	m_Transform.x = 5;
	m_Transform.y = 5;

	m_RigidBody.mass = 0.5f;
}

void GameObjects::SetTransform(float _x, float _y)
{
	m_Transform.x = _x;
	m_Transform.y = _y;
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