#include "ScoreComponent.h"

#include "Achievement.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextRenderObserver.h"
#include "HeroComponent.h"

pac::ScoreComponent::ScoreComponent(dae::GameObject* pOwner, HeroComponent* pHero, TextRenderComponent* pTextRenderComponent)
	: RootComponent(pOwner)
	, Observer<int>()
	, m_Score(0)
	, m_pHero(pHero)
{
	m_pHero->m_Pickup.AddObserver(this);
}

void pac::ScoreComponent::OnNotify(int val)
{
}

void pac::ScoreComponent::OnSubjectDestroyed()
{
}