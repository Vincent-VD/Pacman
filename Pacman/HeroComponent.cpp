#include "HeroComponent.h"

#include "GameTime.h"
#include "ServiceLocator.h"

pac::HeroComponent::HeroComponent(dae::GameObject* pOwner, int health)
	: RootComponent(pOwner)
	, m_Health(health)
{
}

void pac::HeroComponent::ActivatePowerMode()
{
	m_IsPowerModeActive = true;
	m_CurrPowerModeCooldown = 0.f;
}

void pac::HeroComponent::Update()
{
	const float elapsedTime{ dae::GameTime::GetInstance().GetDeltaTime() };
	//if (!m_IsPowerModeActive) return;

	if(m_IsPowerModeActive)
	{
		m_CurrPowerModeCooldown += elapsedTime;
		if (m_CurrPowerModeCooldown >= m_PowerModeLimit)
		{
			m_IsPowerModeActive = false;
			m_CurrPowerModeCooldown = 0.f;
			//m_Menu.Notify("power up");
			auto& soundManager{ dae::ServiceLocator::GetSoundSystem() };
			soundManager.PlaySound({ 4, 1.f, false });
			m_Pickup.Notify(PickupType::reset);
		}
	}

	if(m_HasBeenDamaged)
	{
		m_CurrHitCooldown += elapsedTime;
		if(m_CurrHitCooldown >= m_MaxHitCooldown)
		{
			m_CurrHitCooldown = 0.f;
			m_HasBeenDamaged = false;
		}
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
	if(!m_HasBeenDamaged)
	{
		--m_Health;
		m_Health = std::max(0, m_Health);
		m_HasBeenDamaged = true;
	}
	
	if(m_Health == 0)
	{
		auto& soundManager{ dae::ServiceLocator::GetSoundSystem() };
		soundManager.PlaySound({ 1, 1.f, false });
		m_Menu.Notify("game over");
	}

	m_HealthChanged.Notify();
}

void pac::HeroComponent::Pickup(PickupType type)
{
	m_Pickup.Notify(type);
}
