#pragma once
#include "RootComponent.h"
#include "Observer.h"

namespace dae
{
	class TextRenderComponent;
}

namespace pac
{
	enum class PickupType;
	class HeroComponent;

	class ScoreComponent : public dae::RootComponent, public dae::Observer<PickupType>
	{
	public:
		ScoreComponent(dae::GameObject* pOwner, HeroComponent* pHero, dae::TextRenderComponent* pTextRenderComponent);
		virtual ~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

		int GetScore() const { return m_Score; }

		virtual void OnNotify(PickupType type) override;
		virtual void OnSubjectDestroyed() override;

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		int m_Score;
		HeroComponent* m_pHero;
		dae::TextRenderComponent* m_pTextRenderComponent;
	};
}


