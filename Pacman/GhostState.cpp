#include "GhostState.h"

#include "GameObject.h"
#include "GhostMoveComponent.h"

pac::GhostState::GhostState(dae::GameObject* pActor)
	: m_pOwner(pActor)
{
}

pac::NormalState::NormalState(dae::GameObject* pActor)
	: GhostState(pActor)
{
}

pac::GhostState* pac::NormalState::HandleInput(const std::string& action)
{
	if(action == "power up")
	{
		GetActor()->GetComponent<GhostMoveComponent>()->InvertDirection();
		return new BlueState{ GetActor() };
	}
	return nullptr;
}

void pac::NormalState::OnCollision()
{
	
}

pac::GhostState* pac::NormalState::Update()
{
	return nullptr;
}

pac::BlueState::BlueState(dae::GameObject* pActor)
	: GhostState(pActor)
{
}

pac::GhostState* pac::BlueState::HandleInput(const std::string& /*basic_string*/)
{
	return nullptr;
}

void pac::BlueState::OnCollision()
{
	GetActor()->Destroy();
}

pac::GhostState* pac::BlueState::Update()
{
	return nullptr;
}

pac::WeakState::WeakState(dae::GameObject* pActor)
	: GhostState(pActor)
{
}

pac::GhostState* pac::WeakState::HandleInput(const std::string& /*basic_string*/)
{
	return nullptr;
}

void pac::WeakState::OnCollision()
{
	GhostState::OnCollision();
}

pac::GhostState* pac::WeakState::Update()
{
	return nullptr;
}
