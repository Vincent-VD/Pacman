#include "HeroComponent.h"

pac::HeroComponent::HeroComponent(dae::GameObject* pOwner, int health)
	: RootComponent(pOwner)
	, m_Health(health)
{
}

void pac::HeroComponent::Update()
{
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

	m_HealthChanged.Notify();
}

void pac::HeroComponent::Pickup(PickupType type)
{
	m_Pickup.Notify(type);
}
