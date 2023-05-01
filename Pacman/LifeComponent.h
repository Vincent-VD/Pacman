#pragma once
#include "Observer.h"
#include "RootComponent.h"

namespace pac
{
	class TextRenderComponent;

	class LifeComponent : public dae::RootComponent
	{
	public:
		LifeComponent(dae::GameObject* pOwner, TextRenderComponent* pTextRenderComponent, const int nrOfLives = 3);
		virtual ~LifeComponent() override = default;
		LifeComponent(const LifeComponent& other) = delete;
		LifeComponent(LifeComponent&& other) noexcept = delete;
		LifeComponent& operator=(const LifeComponent& other) = delete;
		LifeComponent& operator=(LifeComponent&& other) noexcept = delete;

		void Hit();

		int GetLivesLeft() const { return m_CurrLives; }

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		int m_CurrLives;
		const int m_MaxLives;
		dae::Subject<int> m_HUDSubject;
		//TextRenderComponent* m_pTextRenderComponent;
	};
}


