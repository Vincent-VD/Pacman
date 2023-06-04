#pragma once
#include <RootComponent.h>

#include "Observer.h"

namespace pac
{
	enum class PickupType
	{
		pellet,
		powerPellet
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
		void ActivatePowerMode();

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override;

		void Damage();
		void Pickup(PickupType type);

		dae::Subject<> m_HealthChanged{};
		dae::Subject<PickupType> m_Pickup{};
		dae::Subject<std::string> m_Menu{};

	private:
		int m_Health;
		bool m_IsPowerModeActive{ false };
		float m_CurrTimer{};
		float m_PowerModeLimit{ 13.f };
	};

}

