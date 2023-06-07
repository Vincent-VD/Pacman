#pragma once
#include <RootComponent.h>

#include "Observer.h"

namespace pac
{
	enum class PickupType
	{
		pellet,
		powerPellet,
		ghost,
		reset
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
		bool IsPowerModeActive() const { return m_IsPowerModeActive; }
		void ActivatePowerMode();

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override;

		void Damage();
		void Pickup(PickupType type);

		dae::Subject<> m_HealthChanged{};
		dae::Subject<PickupType> m_Pickup{};
		dae::Subject<const std::string&> m_Menu{};

	private:
		int m_Health;
		bool m_IsPowerModeActive{ false };
		float m_CurrTimer{};
		const float m_PowerModeLimit{ 13.f };

		bool m_HasBeenDamaged{ false };
		float m_CurrHitCooldown{};
		const float m_MaxHitCooldown{ 2.f };
	};

}

