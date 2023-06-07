#include "GhostState.h"

#include "CollisionTemplates.h"
#include "GameObject.h"
#include "GameTime.h"
#include "GhostCollisionComponent.h"
#include "GhostMoveComponent.h"
#include "TextureComponent2D.h"

pac::GhostState::GhostState(dae::GameObject* pActor)
	: m_pOwner(pActor)
{
}

pac::NormalState::NormalState(dae::GameObject* pActor, const glm::vec2& moveDirection)
	: GhostState(pActor)
	, m_MoveDirection(moveDirection)
{
}

pac::GhostState* pac::NormalState::HandleInput(const std::string& action)
{
	if(action == "power up")
	{
		return new BlueState{ GetActor(), m_MoveDirection };
	}
	return nullptr;
}

pac::GhostState* pac::NormalState::Update()
{
	auto elapsedSec{ dae::GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
	auto nextPos{ currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} *elapsedSec };
	while (GetActor()->GetComponent<GhostCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, (int)Layers::level))
	{
		SetRandomDirection();
		nextPos = currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} *elapsedSec;
	}
	GetActor()->GetTransform()->SetPosition(nextPos);
	return nullptr;
}

void pac::NormalState::OnEnter()
{
	m_pTextureComp = GetActor()->GetComponent<dae::TextureComponent2D>().get();
}

void pac::NormalState::SetRandomDirection()
{
	if (m_pTextureComp == nullptr)
	{
		m_pTextureComp = GetActor()->GetComponent<dae::TextureComponent2D>().get();
	}

	const int rand{ std::rand() % 4 };
	switch (rand)
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

pac::BlueState::BlueState(dae::GameObject* pActor, const glm::vec2& moveDirection)
	: GhostState(pActor)
	, m_MoveDirection(-moveDirection)
{
}

pac::GhostState* pac::BlueState::HandleInput(const std::string& action)
{
	if(action == "collision")
	{
		return new WeakState{ GetActor(), m_MoveDirection };
	}
	if(action == "recover")
	{
		return new NormalState{ GetActor(), m_MoveDirection };
	}
	return nullptr;
}

pac::GhostState* pac::BlueState::Update()
{
	auto elapsedSec{ dae::GameTime::GetInstance().GetDeltaTime() };

	auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
	auto nextPos{ currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} *elapsedSec };
	while (GetActor()->GetComponent<GhostCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, (int)Layers::level))
	{
		SetRandomDirection();
		nextPos = currentPos + m_Speed * glm::vec3{m_MoveDirection.x, m_MoveDirection.y, 0.f} *elapsedSec;
	}
	GetActor()->GetTransform()->SetPosition(nextPos);

	return nullptr;
}

void pac::BlueState::OnEnter()
{
	auto textureComp{ GetActor()->GetComponent<dae::TextureComponent2D>() };
	m_PrevRect = textureComp->GetSourceRect();
	textureComp->SetSourceRect(dae::Rectf{0.f, 6.f * 32.f, 32.f, 32.f});
}

void pac::BlueState::OnExit()
{
	auto textureComp{ GetActor()->GetComponent<dae::TextureComponent2D>() };
	textureComp->SetSourceRect(m_PrevRect);
}

void pac::BlueState::SetRandomDirection()
{
	if (m_pTextureComp == nullptr)
	{
		m_pTextureComp = GetActor()->GetComponent<dae::TextureComponent2D>().get();
	}

	const int rand{ std::rand() % 4 };
	switch (rand)
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
}

pac::WeakState::WeakState(dae::GameObject* pActor, const glm::vec2& moveDirection)
	: GhostState(pActor)
	, m_MoveDirection(moveDirection)
{
}

pac::GhostState* pac::WeakState::HandleInput(const std::string& /*basic_string*/)
{
	return nullptr;
}

pac::GhostState* pac::WeakState::Update()
{
	auto elapsedSec{ dae::GameTime::GetInstance().GetDeltaTime() };

	m_CurrTime += elapsedSec;
	if (m_CurrTime >= m_MaxTime)
	{
		return new NormalState{ GetActor(), m_MoveDirection };
	}
	return nullptr;
}
