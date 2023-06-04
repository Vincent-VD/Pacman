#include "HeroComponent.h"

#include "GameTime.h"
#include "Minigin.h"

pac::HeroComponent::HeroComponent(dae::GameObject* pOwner, int health)
	: RootComponent(pOwner)
	, m_Health(health)
{
}

void pac::HeroComponent::ActivatePowerMode()
{
	m_IsPowerModeActive = true;
}

void pac::HeroComponent::Update()
{
	if (!m_IsPowerModeActive) return;
	m_CurrTimer += dae::GameTime::GetInstance().GetDeltaTime();
	if(m_CurrTimer >= m_PowerModeLimit)
	{
		m_IsPowerModeActive = false;
		m_CurrTimer = 0.f;
	}
}

void pac::HeroComponent::FixedUpdate()
{
}

void pac::HeroComponent::Render() const
{
	RootComponent::Render();
}

void pac::HeroComponent::Damage()
{
	--m_Health;
	m_Health = std::max(0, m_Health);
	if(m_Health == 0)
	{
		dae::Minigin::SetPaused(true);
		m_Menu.Notify("game over");
	}

	m_HealthChanged.Notify();
}

void pac::HeroComponent::Pickup(PickupType type)
{
	m_Pickup.Notify(type);
}
