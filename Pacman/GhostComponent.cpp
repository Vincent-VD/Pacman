#include "GhostComponent.h"

#include "GameTime.h"
#include "GhostState.h"

pac::GhostComponent::GhostComponent(dae::GameObject* pOwner, GhostTypes type, bool acceptInput)
	: RootComponent(pOwner)
	, m_IsPlayerControlled(acceptInput)
	, m_Type(type)
	, m_pState(new NormalState{pOwner, {1, 0}})
{
	m_pState->OnEnter();
}

pac::GhostComponent::~GhostComponent()
{
	delete m_pState;
}

void pac::GhostComponent::Weaken()
{
	StateInput("power up");
}

void pac::GhostComponent::Recover()
{
	StateInput("recover");
};

void pac::GhostComponent::OnCollision()
{
	if (m_IsHit) return;
	m_IsHit = true;

	StateInput("collision");
}

bool pac::GhostComponent::IsWeak() const
{
	if(dynamic_cast<BlueState*>(m_pState))
	{
		return true;
	}
	return false;
}

void pac::GhostComponent::Update()
{
	const float elapsedTime{ dae::GameTime::GetInstance().GetDeltaTime() };

	if(m_IsHit)
	{
		m_CurrCooldown += elapsedTime;
		if (m_CurrCooldown >= m_MaxCooldown)
		{
			m_CurrCooldown = 0.f;
			m_IsHit = false;
		}
	}
	if(!m_IsPlayerControlled)
	{
		const auto newState{ m_pState->Update() };
		if (newState != nullptr)
		{
			m_pState->OnExit();
			delete m_pState;
			m_pState = newState;
			m_pState->OnEnter();
		}
	}
	
}

void pac::GhostComponent::StateInput(const std::string& msg)
{
	const auto newState{ m_pState->HandleInput(msg) };
	if (newState != nullptr)
	{
		m_pState->OnExit();
		delete m_pState;
		m_pState = newState;
		m_pState->OnEnter();
	}
}
