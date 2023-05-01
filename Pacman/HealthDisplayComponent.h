#pragma once
#include "Observer.h"
#include "RootComponent.h"

namespace dae
{
	class TextRenderComponent;
}

namespace pac
{
	class HeroComponent;

	class HealthDisplayComponent : public dae::RootComponent, public dae::Observer<>
	{
	public:
		HealthDisplayComponent(dae::GameObject* pOwner, HeroComponent* pHero, dae::TextRenderComponent* pTextRenderComponent) ;
		virtual ~HealthDisplayComponent() override = default;
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) noexcept = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) noexcept = delete;

		virtual void OnNotify() override;
		virtual void OnSubjectDestroyed() override;

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		HeroComponent* m_pHero;
		dae::TextRenderComponent* m_pTextRenderComponent;
	};
}


