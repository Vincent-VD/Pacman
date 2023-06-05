#include "GhostMoveComponent.h"

#include "MiniginPCH.h"

#include "GameTime.h"
#include "GhostCollisionComponent.h"
#include "GameObject.h"

pac::GhostMoveComponent::GhostMoveComponent(dae::GameObject* pOwner)
	: RootComponent(pOwner)
	, m_MoveDirection(glm::vec2{1, 0})
	, m_Speed(30.f)
{
	SetRandomDirection();
}

void pac::GhostMoveComponent::InvertDirection()
{
	m_MoveDirection = glm::vec2{ -m_MoveDirection.x, -m_MoveDirection.y };
}

void pac::GhostMoveComponent::Update()
{
	auto elapsedSec{ dae::GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetOwner()->GetTransform()->GetWorldPosition() };
	auto nextPos{ currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} * elapsedSec };
	if (!GetOwner()->GetComponent<GhostCollisionComponent>()->CheckCollisionAtPosition(nextPos))
	{
		GetOwner()->GetTransform()->SetPosition(nextPos);
	}else
	{
		SetRandomDirection();
	}
}

void pac::GhostMoveComponent::SetRandomDirection()
{
	const int rand{std::rand() % 4};
	switch(rand)
	{
	case 0:
		m_MoveDirection = { 1, 0 };
		break;
	case 1:
		m_MoveDirection = { 0, 1 };
		break;
	case 2:
		m_MoveDirection = { -1, 0 };
		break;
	case 3:
		m_MoveDirection = { 0, 1 };
		break;
	default:
		break;
	}
}


