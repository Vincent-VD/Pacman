#include "LifeComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextRenderObserver.h"

pac::LifeComponent::LifeComponent(dae::GameObject* pOwner, TextRenderComponent* pTextRenderComponent, const int nrOfLives)
	: RootComponent(pOwner)
	, m_CurrLives(nrOfLives)
	, m_MaxLives(nrOfLives)
	, m_HUDSubject(dae::Subject<int>())
	//, m_pTextRenderComponent(pTextRenderComponent)
{
	auto HUDObserver{ new dae::TextRenderObserver(pTextRenderComponent)};
	m_HUDSubject.AddObserver(HUDObserver);
}

void pac::LifeComponent::Hit()
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