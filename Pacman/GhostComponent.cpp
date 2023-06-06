#include "GhostComponent.h"
#include "GhostState.h"

pac::GhostComponent::GhostComponent(dae::GameObject* pOwner, GhostTypes type)
	: RootComponent(pOwner)
	, Observer<const std::string&>()
	, m_Type(type)
	, m_pState(new NormalState{pOwner})
{
}

pac::GhostComponent::~GhostComponent()
{
	delete m_pState;
}

void pac::GhostComponent::OnNotify(const std::string& msg)
{
	const auto newState{ m_pState->HandleInput(msg) };
	if (newState != nullptr)
	{
		delete m_pState;
		m_pState = newState;
	}
}

void pac::GhostComponent::OnCollision() const
{
	m_pState->OnCollision();
}

void pac::GhostComponent::Update()
{
	const auto newState{ m_pState->Update() };
	if (newState != nullptr)
	{
		delete m_pState;
		m_pState = newState;
	}
}
