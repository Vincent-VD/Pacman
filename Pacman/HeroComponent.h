#pragma once
#include <RootComponent.h>

#include "Observer.h"

namespace pac
{
	enum class PickupType
	{
		apple,
		largeApple
	};

	class HeroComponent : public dae::RootComponent
	{
	public:
		HeroComponent(dae::GameObject* pOwner, int health = 3);
		virtual ~HeroComponent() override = default;
		HeroComponent(const HeroComponent& other) = delete;
		HeroComponent(HeroComponent&& other) noexcept = delete;
		HeroComponent& operator=(const HeroComponent& other) = delete;
		HeroComponent& operator=(HeroComponent&& other) noexcept = delete;

		int GetHealth() const { return m_Health; }

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override;

		void Damage();
		void Pickup(PickupType type);

		dae::Subject<> m_HealthChanged{};
		dae::Subject<PickupType> m_Pickup{};

	private:
		int m_Health;
	};

}

