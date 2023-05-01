#include "ScoreComponent.h"

#include "Achievement.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "HeroComponent.h"

pac::ScoreComponent::ScoreComponent(dae::GameObject* pOwner, HeroComponent* pHero, dae::TextRenderComponent* pTextRenderComponent)
	: RootComponent(pOwner)
	, Observer<PickupType>()
	, m_Score(0)
	, m_pHero(pHero)
	, m_pTextRenderComponent(pTextRenderComponent)
{
	m_pHero->m_Pickup.AddObserver(this);
}

void pac::ScoreComponent::OnNotify(PickupType type)
{
	switch (type)
	{
	case PickupType::apple:
		m_Score += 10;
		break;
	case PickupType::largeApple:
		m_Score += 100;
		break;
	}
	m_pTextRenderComponent->SetText(std::to_string(m_Score));
}

void pac::ScoreComponent::OnSubjectDestroyed()
{
	if (m_pHero)
		m_pHero->m_Pickup.RemoveObserver(this);
}
