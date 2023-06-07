#include "GhostMoveComponent.h"

#include "CollisionTemplates.h"
#include "MiniginPCH.h"

#include "GameTime.h"
#include "GhostCollisionComponent.h"
#include "GameObject.h"
#include "TextureComponent2D.h"

pac::GhostMoveComponent::GhostMoveComponent(dae::GameObject* pOwner)
	: RootComponent(pOwner)
	, m_MoveDirection(glm::vec2{1, 0})
	, m_Speed(30.f)
{
	//SetRandomDirection();
}

void pac::GhostMoveComponent::InvertDirection()
{
	m_MoveDirection = glm::vec2{ -m_MoveDirection.x, -m_MoveDirection.y };
	const int newFrame{ (m_pTextureComp->GetFrame() - 2) % 4 };
	m_pTextureComp->SetFrame(newFrame);
}

void pac::GhostMoveComponent::Update()
{
	auto elapsedSec{ dae::GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetOwner()->GetTransform()->GetWorldPosition() };
	auto nextPos{ currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} * elapsedSec };
	while (GetOwner()->GetComponent<GhostCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, (int)Layers::level))
	{
		SetRandomDirection();
		nextPos = currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} *elapsedSec;
	}
	GetOwner()->GetTransform()->SetPosition(nextPos);
}

void pac::GhostMoveComponent::SetRandomDirection()
{
	if(m_pTextureComp == nullptr)
	{
		m_pTextureComp = GetOwner()->GetComponent<dae::TextureComponent2D>().get();
	}

	const int rand{std::rand() % 4};
	switch(rand)
	{
	case 0:
		m_MoveDirection = { 1, 0 };
		break;
	case 1:
		m_MoveDirection = { 0, -1 };
		break;
	case 2:
		m_MoveDirection = { 0, 1 };
		break;
	case 3:
		m_MoveDirection = { -1, 0 };
		break;
	default:
		break;
	}
	m_pTextureComp->SetFrame(rand);
}


