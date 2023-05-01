#include "LifeComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextRenderObserver.h"

dae::LifeComponent::LifeComponent(GameObject* pOwner, TextRenderComponent* pTextRenderComponent, const int nrOfLives)
	: RootComponent(pOwner)
	, m_CurrLives(nrOfLives)
	, m_MaxLives(nrOfLives)
	, m_HUDSubject(Subject<int>())
	//, m_pTextRenderComponent(pTextRenderComponent)
{
	auto HUDObserver{ new TextRenderObserver(pTextRenderComponent)};
	m_HUDSubject.AddObserver(HUDObserver);
}

void dae::LifeComponent::Hit()
{
	--m_CurrLives;
	//m_pTextRenderComponent->SetText("Lives: " + std::to_string(m_CurrLives));
	m_HUDSubject.Notify(m_CurrLives);
	//GetOwner()->NotifyObservers("player hit");
	//if(m_CurrLives == 0)
	//{
	//	GetOwner()->NotifyObservers("player died");
	//	//player dies
	//}
}