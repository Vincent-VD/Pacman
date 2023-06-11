#include "HealthDisplayComponent.h"

#include "HeroComponent.h"
#include "TextRenderComponent.h"

pac::HealthDisplayComponent::HealthDisplayComponent(dae::GameObject* pOwner, HeroComponent* pHero, dae::TextRenderComponent* pTextRenderComponent)
	: RootComponent(pOwner)
	, Observer<>()
	, m_pHero(pHero)
	, m_pTextRenderComponent(pTextRenderComponent)
{
	m_pHero->m_HealthChanged.AddObserver(this);
	m_pTextRenderComponent->SetText(std::to_string(m_pHero->GetHealth()));
}

void pac::HealthDisplayComponent::OnNotify()
{
	m_pTextRenderComponent->SetText(std::to_string(m_pHero->GetHealth()));
}

void pac::HealthDisplayComponent::OnSubjectDestroyed()
{
	if(m_pHero)
	{
		m_pHero->m_HealthChanged.RemoveObserver(this);
	}
}
